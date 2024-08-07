#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/semaphore.h>
#include <linux/miscdevice.h>
#include <linux/device.h>
#include <linux/sched.h>
#include <linux/workqueue.h>
#include <asm/atomic.h>
#include <stdarg.h>
#include <linux/slab.h>
#include <linux/unistd.h>
#include <linux/un.h>
#include <linux/skbuff.h>
#ifdef CONFIG_HWCONNECTIVITY
#include "hisi_oneimage.h"
#endif
#include "chr_devs.h"
#include "oneimage.h"
#include "board.h"
#include "oal_schedule.h"

static int chr_misc_open(struct inode *fd, struct file *fp);
static ssize_t chr_misc_read(struct file *fp, char __user *buff, size_t count, loff_t *loff);
static long chr_misc_ioctl(struct file* fp, unsigned int cmd, unsigned long arg);
static int chr_misc_release(struct inode *fd, struct file* fp);

static CHR_EVENT g_chr_event;

static int     g_log_enable = CHR_LOG_DISABLE;

static const struct file_operations chr_misc_fops = {
    .owner   = THIS_MODULE,
    .open    = chr_misc_open,
    .read    = chr_misc_read,
    .release = chr_misc_release,
    .unlocked_ioctl    = chr_misc_ioctl,
};

static struct miscdevice chr_misc_dev = {
    .minor = MISC_DYNAMIC_MINOR,
    .name  = CHR_DEV_KMSG_PLAT,
    .fops  = &chr_misc_fops,
};

static int chr_misc_open(struct inode *fd, struct file *fp)
{
    if (CHR_LOG_ENABLE != g_log_enable)
    {
        CHR_ERR("chr %s open fail, module is disable\n", chr_misc_dev.name);
        return -EBUSY;
    }
    CHR_DBG("chr %s open success\n", chr_misc_dev.name);
    return CHR_SUCC;
}

static ssize_t chr_misc_read(struct file *fp, char __user *buff, size_t count, loff_t *loff)
{
    int ret;
    unsigned int __user   *puser = (unsigned int __user *)buff;
    struct sk_buff  *skb   =NULL;

    if (CHR_LOG_ENABLE != g_log_enable)
    {
        CHR_ERR("chr %s read fail, module is disable\n", chr_misc_dev.name);
        return -EBUSY;
    }

    if (count < sizeof(unsigned int))
    {
        CHR_ERR("The user space buff is too small\n");
        return -CHR_EFAIL;
    }

    if (NULL == buff)
    {
        CHR_ERR("chr %s read fail, user buff is NULL", chr_misc_dev.name);
        return -EAGAIN;
    }
    skb = skb_dequeue(&g_chr_event.errno_queue);
    if (NULL == skb)
    {
        if (fp->f_flags & O_NONBLOCK)
        {
            CHR_DBG("Thread read chr with NONBLOCK mode\n");
            /* for no data with O_NONBOCK mode return 0 */
            return 0;
        }
        else
        {
            if (wait_event_interruptible(g_chr_event.errno_wait, 
                        NULL != (skb = skb_dequeue(&g_chr_event.errno_queue))))
            {
                if(NULL != skb)
                {
                    skb_queue_head(&g_chr_event.errno_queue, skb);
                }
                CHR_WARNING("Thread interrupt with signel\n");
                return -ERESTARTSYS;
            }
        }
    }
    ret = copy_to_user(puser, skb->data, sizeof(unsigned int));
    if (ret)
    {
        CHR_WARNING("copy_to_user err!restore it, len=%d\n", (int)sizeof(unsigned int));
        skb_queue_head(&g_chr_event.errno_queue, skb);
        return -EFAULT;
    }
    kfree_skb(skb);

    return sizeof(unsigned int);
}

static int chr_write_errno_to_queue(unsigned int ul_errno)
{
    struct sk_buff  *skb   =NULL;

    if(skb_queue_len(&g_chr_event.errno_queue) > CHR_ERRNO_QUEUE_MAX_LEN)
    {
        CHR_WARNING("chr errno queue is full, dispose errno=%x\n", ul_errno);
        return CHR_SUCC;
    }

    /* for code run in interrupt context */
    skb = alloc_skb(sizeof(unsigned int), oal_in_interrupt() ? GFP_ATOMIC : GFP_KERNEL);
    if( NULL == skb)
    {
        CHR_ERR("chr errno alloc skbuff failed! len=%d, errno=%x\n", (int)sizeof(unsigned int), ul_errno);
        return -ENOMEM;
    }

    skb_put(skb, sizeof(unsigned int));
    *(unsigned int*)skb->data = ul_errno;
    skb_queue_tail(&g_chr_event.errno_queue, skb);
    wake_up_interruptible(&g_chr_event.errno_wait);
    return CHR_SUCC;
}

static long chr_misc_ioctl(struct file* fp, unsigned int cmd, unsigned long arg)
{
    unsigned int __user   *puser = (unsigned int __user *)arg;
    unsigned int ret, value = 0;

    if (CHR_LOG_ENABLE != g_log_enable)
    {
        CHR_ERR("chr %s ioctl fail, module is disable\n", chr_misc_dev.name);
        return -EBUSY;
    }

    if (CHR_MAGIC != _IOC_TYPE(cmd))
    {
        CHR_ERR("chr %s ioctl fail, the type of cmd is error type is %d\n",
                                            chr_misc_dev.name, _IOC_TYPE(cmd));
        return -EINVAL;
    }

    if (CHR_MAX_NR < _IOC_NR(cmd))
    {
        CHR_ERR("chr %s ioctl fail, the nr of cmd is error, nr is %d\n",
                                            chr_misc_dev.name, _IOC_NR(cmd));
        return -EINVAL;
    }

    switch (cmd)
    {
    case CHR_ERRNO_WRITE:
        ret = get_user(value, puser);
        if (ret)
        {
            CHR_ERR("chr %s ioctl fail, get data from user fail", chr_misc_dev.name);
            return -EINVAL;
        }
        chr_write_errno_to_queue(value);
        break ;
    default :
        CHR_WARNING("chr ioctl not support cmd=0x%x\n", cmd);
        return -EINVAL;
    }
    return CHR_SUCC;
}

static int chr_misc_release(struct inode *fd, struct file* fp)
{
    if (CHR_LOG_ENABLE != g_log_enable)
    {
        CHR_ERR("chr %s release fail, module is disable\n", chr_misc_dev.name);
        return -EBUSY;
    }
    CHR_DBG("chr %s release success\n", chr_misc_dev.name);
    return CHR_SUCC;
}

int __chr_printLog(CHR_LOGPRIORITY prio, CHR_DEV_INDEX dev_index, const char *fmt,...)
{
    return CHR_SUCC;
}
EXPORT_SYMBOL(__chr_printLog);

int  __chr_exception(unsigned int errno)
{
    if (CHR_LOG_ENABLE != g_log_enable)
    {
        CHR_DBG("chr throw exception fail, module is disable\n");
        return -CHR_EFAIL;
    }

    chr_write_errno_to_queue(errno);
    return CHR_SUCC;
}
EXPORT_SYMBOL(__chr_exception);

void chr_dev_exception_callback(void *buff, unsigned short len)
{
    CHR_DEV_EXCEPTION_STRU* chr_dev_exception = NULL;

    if (NULL == buff)
    {
        CHR_WARNING("chr recv device errno fail, buff is NULL\n");
        return;
    }

    if (len != sizeof(CHR_DEV_EXCEPTION_STRU))
    {
        CHR_WARNING("chr recv device errno fail, len %d is unavailable\n", (int)len);
        return;
    }

    chr_dev_exception = (CHR_DEV_EXCEPTION_STRU*)buff;
    if ((CHR_DEV_FRAME_START != chr_dev_exception->framehead) || (CHR_DEV_FRAME_END != chr_dev_exception->frametail))
    {
        CHR_WARNING("chr recv device errno fail, data is destoried\n");
        return;
    }

    __chr_exception(chr_dev_exception->errno);
    CHR_DBG("chr recv device errno = 0x%x\n", chr_dev_exception->errno);
}
EXPORT_SYMBOL(chr_dev_exception_callback);

int chr_miscdevs_init(void)
{
    int ret = 0;
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    if (!is_my_chip()) {
        CHR_INFO("cfg chr log chip type is not match, skip driver init");
        g_log_enable = CHR_LOG_DISABLE;
        return -EINVAL;
    } else {
        CHR_INFO("cfg chr log is matched with hi110x, continue");
    }
#endif
    init_waitqueue_head(&g_chr_event.errno_wait);
    skb_queue_head_init(&g_chr_event.errno_queue);

    ret = misc_register(&chr_misc_dev);
    if (CHR_SUCC != ret)
    {
        CHR_ERR("chr module init fail\n");
        return -CHR_EFAIL;
    }
    g_log_enable = CHR_LOG_ENABLE;
    CHR_INFO("chr module init succ\n");

    return CHR_SUCC;
}

void chr_miscdevs_exit(void)
{
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    if (!is_my_chip()) {
        CHR_INFO("cfg chr log chip type is not match, skip driver init");
        return;
    } else {
        CHR_INFO("cfg chr log is matched with hi110x, continue");
    }
#endif
    if (CHR_LOG_ENABLE != g_log_enable)
    {
        CHR_INFO("chr module is diabled\n");
        return ;
    }

    misc_deregister(&chr_misc_dev);
    g_log_enable = CHR_LOG_DISABLE;
    CHR_INFO("chr module exit succ\n");
}

MODULE_AUTHOR("Hisilicon platform Driver Group");
MODULE_DESCRIPTION("hi110x chr log driver");
MODULE_LICENSE("GPL");

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


