#ifndef __MNTN_PUBLIC_INTERFACE_H__
#define __MNTN_PUBLIC_INTERFACE_H__ 
#include "soc_acpu_baseaddr_interface.h"
#include "pmic_interface.h"
#include "global_ddr_map.h"
#define PMU_RESET_REG_OFFSET (PMIC_HRST_REG0_ADDR(0)<<2)
#define RST_FLAG_MASK (0xFF)
#define PMU_RESET_VALUE_USED 0xFFFFFF00
#define PMU_RESET_RECORD_DDR_AREA_SIZE 0x100
#define RECORD_PC_STR_MAX_LENGTH 0x48
typedef struct
{
 char exception_info[RECORD_PC_STR_MAX_LENGTH];
 unsigned long exception_info_len;
}
AP_RECORD_PC;
#define ETR_MAGIC_START "ETRTRACE"
#define ETR_MAGIC_SIZE ((unsigned int)sizeof(ETR_MAGIC_START))
typedef struct
{
    char magic[ETR_MAGIC_SIZE];
    u64 paddr;
    u32 size;
    u32 rd_offset;
}
AP_RECORD_ETR;
#define BOARD_COLD_START_ADDR ((HISI_RESERVED_MNTN_PHYMEM_BASE_UNIQUE) + 0x280)
#define FPGA_RESET_REG_ADDR ((HISI_RESERVED_MNTN_PHYMEM_BASE_UNIQUE) + 0x288)
#define FPGA_BOOTUP_KEYPOINT_ADDR ((HISI_RESERVED_MNTN_PHYMEM_BASE_UNIQUE) + 0x290)
#define BOOTUP_KEYPOINT_OFFSET (PMIC_HRST_REG1_ADDR(0)<<2)
#define DFX_HEAD_SIZE 512
#define TOTAL_NUMBER 5
#define FASTBOOTLOG_SIZE HISI_SUB_RESERVED_FASTBOOT_LOG_PYHMEM_SIZE
#define LAST_KMSG_SIZE HISI_RESERVED_PSTORE_PHYMEM_SIZE/2
#define LAST_APPLOG_SIZE HISI_RESERVED_PSTORE_PHYMEM_SIZE/8
#define EVERY_NUMBER_SIZE (DFX_HEAD_SIZE + LAST_APPLOG_SIZE + LAST_KMSG_SIZE + FASTBOOTLOG_SIZE)
#define DFX_MAGIC_NUMBER 0x2846579
#define DFX_USED_SIZE (EVERY_NUMBER_SIZE*(TOTAL_NUMBER+1)+DFX_HEAD_SIZE)
struct dfx_head_info {
 int magic;
 int total_number;
 int cur_number;
 int need_save_number;
 u64 every_number_addr[TOTAL_NUMBER];
 u64 every_number_size;
 u64 temp_number_addr;
};
struct every_number_info {
 u64 rtc_time;
 u64 bootup_keypoint;
 u64 reboot_type;
 u64 fastbootlog_start_addr;
 u64 fastbootlog_size;
 u64 last_kmsg_start_addr;
 u64 last_kmsg_size;
 u64 last_applog_start_addr;
 u64 last_applog_size;
};
enum boot_stage_point
{
 STAGE_START = 1,
 STAGE_XLOADER_START = STAGE_START,
 STAGE_XLOADER_EMMC_INIT_FAIL = 2,
 STAGE_XLOADER_EMMC_INIT_OK = 3,
 STAGE_XLOADER_DDR_INIT_FAIL = 4,
 STAGE_XLOADER_DDR_INIT_OK = 5,
 STAGE_XLOADER_RD_VRL_FAIL = 6,
 STAGE_XLOADER_CHECK_VRL_ERROR = 7,
 STAGE_XLOADER_IMG_TOO_LARGE = 8,
 STAGE_XLOADER_READ_FASTBOOT_FAIL = 9,
 STAGE_XLOADER_LOAD_HIBENCH_FAIL = 10,
 STAGE_XLOADER_SEC_VERIFY_FAIL = 11,
 STAGE_XLOADER_GET_IMGSIZE_FAIL = 12,
 STAGE_XLOADER_IMGSIZE_ERROR = 13,
 STAGE_XLOADER_VRL_CHECK_ERROR = 14,
 STAGE_XLOADER_SECURE_VERIFY_ERROR = 15,
 STAGE_XLOADER_LOAD_FASTBOOT_START = 16,
 STAGE_XLOADER_LOAD_FASTBOOT_END = 17,
 STAGE_XLOADER_END = 25,
 STAGE_FASTBOOT_START = 26,
 STAGE_FASTBOOT_EMMC_INIT_START = 27,
 STAGE_FASTBOOT_EMMC_INIT_FAIL = 28,
 STAGE_FASTBOOT_EMMC_INIT_OK = 29,
 STAGE_FASTBOOT_DDR_INIT_START = 30,
 STAGE_FASTBOOT_DISPLAY_INIT_START = 31,
 STAGE_FASTBOOT_PRE_BOOT_INIT_START = 32,
 STAGE_FASTBOOT_LD_OTHER_IMGS_START = 33,
 STAGE_FASTBOOT_LD_KERNEL_IMG_START = 34,
 STAGE_FASTBOOT_BOOT_KERNEL_START = 35,
 STAGE_FASTBOOT_LOADLPMCU_FAIL = 38,
 STAGE_FASTBOOT_SECBOOT_INIT_START = 39,
 STAGE_FASTBOOT_END = 70,
 STAGE_KERNEL_EARLY_INITCALL = 75,
 STAGE_KERNEL_PURE_INITCALL = 77,
 STAGE_KERNEL_CORE_INITCALL = 79,
 STAGE_KERNEL_CORE_INITCALL_SYNC = 81,
 STAGE_KERNEL_POSTCORE_INITCALL = 83,
 STAGE_KERNEL_POSTCORE_INITCALL_SYNC = 85,
 STAGE_KERNEL_ARCH_INITCALL = 87,
 STAGE_KERNEL_ARCH_INITCALLC = 89,
 STAGE_KERNEL_SUBSYS_INITCALL = 81,
 STAGE_KERNEL_SUBSYS_INITCALL_SYNC = 83,
 STAGE_KERNEL_FS_INITCALL = 85,
 STAGE_KERNEL_FS_INITCALL_SYNC = 87,
 STAGE_KERNEL_ROOTFS_INITCALL = 89,
 STAGE_KERNEL_DEVICE_INITCALL = 91,
 STAGE_KERNEL_DEVICE_INITCALL_SYNC = 93,
 STAGE_KERNEL_LATE_INITCALL = 95,
 STAGE_KERNEL_LATE_INITCALL_SYNC = 97,
 STAGE_KERNEL_CONSOLE_INITCALL = 99,
 STAGE_KERNEL_SECURITY_INITCALL = 101,
 STAGE_KERNEL_BOOTANIM_COMPLETE = 103,
 STAGE_INIT_INIT_START = 110,
 STAGE_INIT_ON_EARLY_INIT = 111,
 STAGE_INIT_ON_INIT = 112,
 STAGE_INIT_ON_EARLY_FS = 113,
 STAGE_INIT_ON_FS = 114,
 STAGE_INIT_ON_POST_FS = 115,
 STAGE_INIT_ON_POST_FS_DATA = 116,
 STAGE_INIT_ON_EARLY_BOOT = 117,
 STAGE_INIT_ON_BOOT = 118,
 STAGE_ANDROID_ZYGOTE_START = 150,
 STAGE_ANDROID_VM_START = 151,
 STAGE_ANDROID_PHASE_WAIT_FOR_DEFAULT_DISPLAY = 152,
 STAGE_ANDROID_PHASE_LOCK_SETTINGS_READY = 153,
 STAGE_ANDROID_PHASE_SYSTEM_SERVICES_READY = 154,
 STAGE_ANDROID_PHASE_ACTIVITY_MANAGER_READY = 155,
 STAGE_ANDROID_PHASE_THIRD_PARTY_APPS_CAN_START = 156,
 STAGE_ANDROID_BOOT_SUCCESS = 250,
 STAGE_BOOTUP_END = STAGE_ANDROID_BOOT_SUCCESS,
 STAGE_END = 255,
};
enum himntnEnum
{
    HIMNTN_NVE_VALID = 0,
    HIMNTN_WDT_MIN,
    HIMNTN_AP_WDT = HIMNTN_WDT_MIN,
    HIMNTN_GLOBAL_WDT,
    HIMNTN_MODEM_WDT,
    HIMNTN_LPM3_WDT,
    HIMNTN_IOM3_WDT,
    HIMNTN_HIFI_WDT,
    HIMNTN_SECOS_WDT,
    HIMNTN_ISP_WDT,
    HIMNTN_IVP_WDT,
    HIMNTN_OCBC_WDT = 10,
    HIMNTN_UCE_WDT,
    HIMNTN_RESERVED_WDT3,
    HIMNTN_WDT_MAX = HIMNTN_RESERVED_WDT3,
    HIMNTN_FST_DUMP_MEM,
    HIMNTN_MNTN_DUMP_MEM,
    HIMNTN_SD2JTAG,
    HIMNTN_PRESS_KEY_TO_FASTBOOT,
    HIMNTN_PANIC_INTO_LOOP,
    HIMNTN_GOBAL_RESETLOG,
    HIMNTN_NOC_INT_HAPPEN,
    HIMNTN_NOC_ERROR_REBOOT = 20,
    HIMNTN_DFXPARTITION_TO_FILE,
    HIMNTN_DDR_ERROR_REBOOT,
    HIMNTN_HISEE,
    HIMNTN_WATCHPOINT_EN,
    HIMNTN_KMEMLEAK_SWITCH,
    HIMNTN_FB_PANIC_REBOOT,
    HIMNTN_MEM_TRACE = 27,
    HIMNTN_FTRACE,
    HIMNTN_EAGLE_EYE,
    HIMNTN_KERNEL_DUMP_ENABLE = 30,
    HIMNTN_SD2DJTAG,
    HIMNTN_MMC_TRACE,
    HIMNTN_LPM3_PANIC_INTO_LOOP,
    HIMNTN_TRACE_CLK_REGULATOR,
    HIMNTN_CORESIGHT,
    HIMNTN_RESERVED3,
    HIMNTN_RESERVED4,
    HIMNTN_RESERVED5,
    HIMNTN_BOTTOM
};
typedef enum
{
    AP_S_COLDBOOT = 0x0,
    BOOTLOADER = 0x01,
    RECOVERY = 0x02,
    RESETFACTORY = 0x03,
    RESETUSER = 0x04,
    SDUPDATE = 0x05,
    CHARGEREBOOT = 0x06,
    RESIZE = 0x07,
    ERECOVERY = 0x08,
    USBUPDATE = 0x09,
    CUST = 0x0a,
    OEM_RTC = 0x0c,
    RESERVED5 = 0x0d,
    MOUNTFAIL = 0x0e,
    HUNGDETECT = 0x0f,
    COLDBOOT = 0x10,
    RESERVED1 = 0x11,
    AP_S_FASTBOOTFLASH = 0x13,
    REBOOT_REASON_LABEL1 = 0x14,
    AP_S_ABNORMAL = REBOOT_REASON_LABEL1,
    AP_S_TSENSOR0 = 0x15,
    AP_S_TSENSOR1 = 0x16,
    AP_S_AWDT = 0x17,
    LPM3_S_GLOBALWDT = 0x18,
    G3D_S_G3DTSENSOR = 0x19,
    LPM3_S_LPMCURST = 0x1a,
    CP_S_CPTSENSOR = 0x1b,
    IOM3_S_IOMCURST = 0x1c,
    ASP_S_ASPWD = 0x1d,
    CP_S_CPWD = 0x1e,
    IVP_S_IVPWD = 0x1f,
    ISP_S_ISPWD = 0x20,
    AP_S_DDR_UCE_WD = 0x21,
    AP_S_DDR_FATAL_INTER = 0X22,
    OCBC_S_WD = 0x23,
    REBOOT_REASON_LABEL2 = 0x24,
    AP_S_PANIC = REBOOT_REASON_LABEL2,
    AP_S_NOC = 0x25,
    RESERVED2 = 0x26,
    AP_S_DDRC_SEC = 0x27,
    AP_S_F2FS = 0x28,
    AP_S_COMBINATIONKEY = 0x29,
    RESERVED6 = 0x2a,
    AP_S_MAILBOX = 0x2b,
    REBOOT_REASON_LABEL3 = 0x2c,
    CP_S_MODEMDMSS = REBOOT_REASON_LABEL3,
    CP_S_MODEMNOC = 0x2d,
    CP_S_MODEMAP = 0x2e,
    CP_S_EXCEPTION = 0x2f,
    CP_S_RESETFAIL = 0x30,
    CP_S_NORMALRESET = 0x31,
    LPM3_S_EXCEPTION = 0x32,
    SOCHIFI_S_EXCEPTION = 0x33,
    HIFI_S_RESETFAIL = 0x34,
    ISP_S_EXCEPTION = 0x35,
    IVP_S_EXCEPTION = 0x36,
    IOM3_S_EXCEPTION = 0x37,
    TEE_S_EXCEPTION = 0x38,
    MMC_S_EXCEPTION = 0x39,
    CODECHIFI_S_EXCEPTION = 0x3a,
    CP_S_RILD_EXCEPTION = 0x3b,
    CP_S_3RD_EXCEPTION = 0x3c,
    IOM3_S_USER_EXCEPTION = 0x3d,
    HISEE_S_EXCEPTION = 0x3e,
    REBOOT_REASON_LABEL4 = 0x40,
    RESERVED4 = REBOOT_REASON_LABEL4,
    BR_KEY_VOLUMN_DOWN_UP_UPDATE_USB = 0x41,
    BR_KEY_VOLUMN_DOWN_UP_UPDATE_SD_FORCE = 0x42,
    BR_KEY_VOLUMN_UP = 0x43,
    BR_KEY_POWERON_PRESS_1S = 0x44,
    BR_KEY_POWERON_PRESS_10S = 0x45,
    BR_CHECKPOINT_RECOVERY = 0x46,
    BR_CHECKPOINT_ERECOVERY = 0x47,
    BR_CHECKPOINT_SDUPDATE = 0x48,
    BR_CHECKPOINT_USBUPDATE = 0x49,
    BR_CHECKPOINT_RESETFACTORY = 0x4a,
    BR_CHECKPOINT_HOTAUPDATE = 0x4b,
    BR_POWERON_BY_USB_NO_BAT = 0x4d,
    BR_NOGUI = 0x4e,
    BR_FACTORY_VERSION = 0x4f,
    BR_RESET_HAPPEN = 0x50,
    BR_POWEROFF_ALARM = 0x51,
    BR_POWEROFF_CHARGE = 0x52,
    BR_POWERON_BY_SMPL = 0x53,
    BR_CHECKPOINT_UPDATEDATAIMG = 0x54,
    BR_REBOOT_CPU_BUCK = 0x55,
    REBOOT_REASON_LABEL5 = 0x65,
    AP_S_PMU = REBOOT_REASON_LABEL5,
    AP_S_SMPL = 0x66,
    AP_S_SCHARGER = 0x67,
    REBOOT_REASON_LABEL6 = 0x6A,
    XLOADER_S_DDRINIT_FAIL = REBOOT_REASON_LABEL6,
    XLOADER_S_EMMCINIT_FAIL = 0x6B,
    XLOADER_S_LOAD_FAIL = 0x6C,
    XLOADER_S_VERIFY_FAIL = 0x6D,
    XLOADER_S_WATCHDOG = 0x6E,
    REBOOT_REASON_LABEL7 = 0x74,
    FASTBOOT_S_EMMCINIT_FAIL = REBOOT_REASON_LABEL7,
    FASTBOOT_S_PANIC = 0x75,
    FASTBOOT_S_WATCHDOG = 0x76,
    AP_S_PRESS6S = 0x77,
    FASTBOOT_S_OCV_VOL_ERR = 0x78,
    FASTBOOT_S_BAT_TEMP_ERR = 0x79,
    FASTBOOT_S_MISC_ERR = 0x7A,
    FASTBOOT_S_LOAD_DTIMG_ERR = 0x7B,
    FASTBOOT_S_LOAD_OTHER_IMGS_ERR = 0x7C,
    FASTBOOT_S_KERNEL_IMG_ERR = 0x7D,
    FASTBOOT_S_LOADLPMCU_FAIL = 0x7E,
    FASTBOOT_S_IMG_VERIFY_FAIL = 0x7F,
    REBOOT_REASON_LABEL8 = 0x89,
    REBOOT_REASON_LABEL9 = 0x90,
    BFM_S_BOOT_NATIVE_BOOT_FAIL = REBOOT_REASON_LABEL9,
    BFM_S_BOOT_TIMEOUT,
    BFM_S_BOOT_FRAMEWORK_BOOT_FAIL,
    BFM_S_BOOT_NATIVE_DATA_FAIL,
    REBOOT_REASON_LABEL10 = 0xB0,
} EXCH_SOURCE;
enum MODID_LIST {
    HISI_BB_MOD_MODEM_DRV_START = 0x00000000,
    HISI_BB_MOD_MODEM_DRV_END = 0x0fffffff,
    HISI_BB_MOD_MODEM_OSA_START = 0x10000000,
    HISI_BB_MOD_MODEM_OSA_END = 0x1fffffff,
    HISI_BB_MOD_MODEM_OM_START = 0x20000000,
    HISI_BB_MOD_MODEM_OM_END = 0x2fffffff,
    HISI_BB_MOD_MODEM_GU_L2_START = 0x30000000,
    HISI_BB_MOD_MODEM_GU_L2_END = 0x3fffffff,
    HISI_BB_MOD_MODEM_GU_WAS_START = 0x40000000,
    HISI_BB_MOD_MODEM_GU_WAS_END = 0x4fffffff,
    HISI_BB_MOD_MODEM_GU_GAS_START = 0x50000000,
    HISI_BB_MOD_MODEM_GU_GAS_END = 0x5fffffff,
    HISI_BB_MOD_MODEM_GU_NAS_START = 0x60000000,
    HISI_BB_MOD_MODEM_GU_NAS_END = 0x6fffffff,
    HISI_BB_MOD_MODEM_GU_DSP_START = 0x70000000,
    HISI_BB_MOD_MODEM_GU_DSP_END = 0x7fffffff,
    HISI_BB_MOD_AP_START = 0x80000000,
    HISI_BB_MOD_AP_END = 0x81fff0ff,
    HISI_BB_MOD_BFM_START = 0x81fff100,
    HISI_BB_MOD_BFM_END = 0x81fff1ff,
    HISI_BB_MOD_FASTBOOT_START = 0x81fff200,
    HISI_BB_MOD_FASTBOOT_END = 0x81fffcff,
    HISI_BB_MOD_ISP_START = 0x81fffd00,
    HISI_BB_MOD_ISP_END = 0x81fffeff,
    HISI_BB_MOD_EMMC_START = 0x81ffff00,
    HISI_BB_MOD_EMMC_END = 0x81ffffff,
    HISI_BB_MOD_CP_START = 0x82000000,
    HISI_BB_MOD_CP_END = 0x82ffffff,
    HISI_BB_MOD_TEE_START = 0x83000000,
    HISI_BB_MOD_TEE_END = 0x83ffffff,
    HISI_BB_MOD_HIFI_START = 0x84000000,
    HISI_BB_MOD_HIFI_END = 0x84ffffff,
    HISI_BB_MOD_LPM_START = 0x85000000,
    HISI_BB_MOD_LPM_END = 0x85ffffff,
    HISI_BB_MOD_IOM_START = 0x86000000,
    HISI_BB_MOD_IOM_END = 0x86ffffff,
    HISI_BB_MOD_HISEE_START = 0x87000000,
    HISI_BB_MOD_HISEE_END = 0x87ffffff,
    HISI_BB_MOD_RESERVED_START = 0x88000000,
    HISI_BB_MOD_RESERVED_END = 0x9fffffff,
    HISI_BB_MOD_MODEM_LPS_START = 0xa0000000,
    HISI_BB_MOD_MODEM_LPS_END = 0xafffffff,
    HISI_BB_MOD_MODEM_LMSP_START = 0xb0000000,
    HISI_BB_MOD_MODEM_LMSP_END = 0xbfffffff,
    HISI_BB_MOD_RANDOM_ALLOCATED_START = 0xc0000000,
    HISI_BB_MOD_RANDOM_ALLOCATED_END = 0xf0ffffff
};
enum CORE_LIST {
    RDR_AP = 0x1,
    RDR_CP = 0x2,
    RDR_TEEOS = 0x4,
    RDR_HIFI = 0x8,
    RDR_LPM3 = 0x10,
    RDR_IOM3 = 0x20,
    RDR_ISP = 0x40,
    RDR_IVP = 0x80,
    RDR_EMMC = 0x100,
    RDR_MODEMAP = 0x200,
    RDR_CLK = 0x400,
    RDR_REGULATOR = 0x800,
    RDR_BFM = 0x1000,
    RDR_HISEE = 0x2000,
    RDR_CORE_MAX = 14
};
#define FTRACE_MDUMP_MAGIC 0xF748FDE2
#define FTRACE_BUF_MAX_SIZE 0x400000
#define FTRACE_DUMP_NAME "ftrace"
#define FTRACE_DUMP_FS_NAME "/proc/balong/memory/"FTRACE_DUMP_NAME
typedef struct
{
    u64 magic;
    u64 paddr;
    u32 size;
}
FTRACE_MDUMP_HEAD;
#define DTS_MNTNDUMP_NAME "/reserved-memory/mntndump"
#define MNTNDUMP_MAGIC (0xDEADBEEFDEADBEEF)
#define MAX_LEN_OF_MNTNDUMP_ADDR_STR (0x20)
#define MNTN_DUMP_VERSION (0xFFFF0002)
typedef enum {
    MNTN_DUMP_HEAD,
    MNTN_DUMP_ETR,
    MNTN_DUMP_KERNEL_DUMP,
    MNTN_DUMP_PANIC,
    MNTN_DUMP_FTRACE,
    MNTN_DUMP_PSTORE_RAMOOPS,
    MNTN_DUMP_MAX
}mntn_dump_module;
#define MNTN_DUMP_HEAD_SIZE (sizeof(struct mdump_head))
#define MNTN_DUMP_ETR_SIZE (0x30)
#define MNTN_DUMP_KERNEL_DUMP_SIZE (0x300)
#define MNTN_DUMP_PANIC_SIZE (0x100)
#define MNTN_DUMP_FTRACE_SIZE (0x30)
#define MNTN_DUMP_PSTORE_RAMOOPS_SIZE (0x30)
#define MNTN_DUMP_MAXSIZE (0x1000)
struct mdump_regs_info{
 int mid;
 unsigned int offset;
 unsigned int size;
} ;
struct mdump_head{
 unsigned long magic;
 unsigned int version;
 unsigned int nums;
 struct mdump_regs_info regs_info[MNTN_DUMP_MAX];
};
struct mdump_end{
 unsigned long magic;
};
struct mdump_pstore {
 unsigned long magic;
 unsigned long ramoops_addr;
 unsigned long ramoops_size;
};
#endif
