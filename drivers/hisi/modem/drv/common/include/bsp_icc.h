/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
 * foss@huawei.com
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is free software; you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License version 2 and 
 * * only version 2 as published by the Free Software Foundation.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program; if not, write to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary forms, with or without
 * * modification, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the distribution.
 * * 3) Neither the name of Huawei nor the names of its contributors may 
 * *    be used to endorse or promote products derived from this software 
 * *    without specific prior written permission.
 * 
 * * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */
#ifndef __BSP_ICC_H__
#define __BSP_ICC_H__

#ifdef __cplusplus /* __cplusplus */
extern "C"
{
#endif /* __cplusplus */

#include <osl_common.h>
#include <bsp_sram.h>
#include <bsp_shared_ddr.h>
#include <mdrv_icc_common.h>
#include <bsp_ipc.h>

#define ICC_CHAN_NUM_MAX            (32)
int BSP_ICC_Open(unsigned int u32ChanId, ICC_CHAN_ATTR_S *pChanAttr);
s32 BSP_ICC_Close(u32 u32ChanId);
int BSP_ICC_Write(unsigned int u32ChanId, unsigned char* pData, int s32Size);
int BSP_ICC_Read(unsigned int u32ChanId, unsigned char* pData, int s32Size);
s32 BSP_ICC_Ioctl(u32 u32ChanId, u32 cmd, void *param);
s32 BSP_ICC_Debug_Register(u32 u32ChanId, FUNCPTR_1 debug_routine, int param);
/* from drv_icc.h start*/

#define ICC_BUSY              (0x03 | NOTIFY_STOP_MASK)
#define ICC_OK                (0)
#define ICC_ERR               (-1)

enum CPU_ID
{
	ICC_CPU_MIN = IPC_CORE_ACORE,
	ICC_CPU_APP = IPC_CORE_ACORE,
	ICC_CPU_MODEM = IPC_CORE_CCORE,
	ICC_CPU_MCU = IPC_CORE_MCORE,
	ICC_CPU_TLDSP = IPC_CORE_LDSP,
	ICC_CPU_HIFI = IPC_CORE_HiFi,
	ICC_CPU_MAX
};

enum ICC_ERR_NO
{
	ICC_CHN_INIT_FAIL = (0x80000000 + (0 << 16)),
	ICC_MALLOC_CHANNEL_FAIL,
	ICC_MALLOC_VECTOR_FAIL,
	ICC_CREATE_TASK_FAIL,
	ICC_DEBUG_INIT_FAIL,
	ICC_CREATE_SEM_FAIL,
	ICC_REGISTER_INT_FAIL,
	ICC_INVALID_PARA,
	ICC_WAIT_SEM_TIMEOUT,
	ICC_SEND_ERR,
	ICC_RECV_ERR,
	ICC_REGISTER_CB_FAIL,
	ICC_REGISTER_DPM_FAIL,
	ICC_MALLOC_MEM_FAIL,
	ICC_NULL_PTR,
	ICC_INIT_ADDR_TOO_BIG,
	ICC_INIT_SKIP

};

enum ICC_CHN_ID
{
	ICC_CHN_ACORE_CCORE_MIN=0,
	ICC_CHN_IFC = 0,
	ICC_CHN_RFILE = 1,
	ICC_CHN_NV = 2,
	ICC_CHN_GUOM0 = 3,
	ICC_CHN_GUOM1,
	ICC_CHN_GUOM2,
	ICC_CHN_GUOM3,
	ICC_CHN_GUOM4,
	ICC_CHN_GUOM5,
	ICC_CHN_CSHELL,
	ICC_CHN_AC_PANRPC,
	ICC_CHN_ACORE_CCORE_MAX,
	ICC_CHN_MCORE_CCORE,
	ICC_CHN_MCORE_ACORE,
	ICC_CHN_CCPU_HIFI_VOS_MSG,
	ICC_CHN_HIFI_TPHY_MSG,
	ICC_CHN_VT_VOIP,
	ICC_CHN_SEC_IFC,
	ICC_CHN_SEC_VSIM,
	ICC_CHN_ID_MAX
};

enum ICC_RECV_FUNC_ID{
	IFC_RECV_FUNC_RTC_SETTIME = 0,
	IFC_RECV_FUNC_ONOFF,
	IFC_RECV_FUNC_ANTEN,
	IFC_RECV_FUNC_EFUSE,
	IFC_RECV_FUNC_SIM0,
	IFC_RECV_FUNC_SIM1,
	IFC_RECV_FUNC_CSHELL,
	IFC_RECV_FUNC_UART,
    IFC_RECV_FUNC_LED,
    IFC_RECV_FUNC_RESET,
    FC_RECV_FUNC_GPSCLK,
	IFC_RECV_FUNC_PASTAR,
    IFC_RECV_FUNC_PA_RF,
    IFC_RECV_FUNC_WAKEUP,
	IFC_RECV_FUNC_PM_OM,
	IFC_RECV_FUNC_SOCP_DEBUG,
	IFC_RECV_FUNC_REMOTE_CLK,
    IFC_RECV_FUNC_PMU_OCP,
	IFC_RECV_FUNC_SYSTEM_HEATING,
	IFC_RECV_FUNC_SYS_BUS,
	IFC_RECV_FUNC_LOADPS,

	IFC_RECV_FUNC_TEST1,
	IFC_RECV_FUNC_ID_MAX,

	RFILE_RECV_FUNC_ID = 0,

	RFILE_RECV_FUNC_ID_MAX,

    NV_RECV_FUNC_AC = 0,
    NV_RECV_FUNC_SC = 1,

	NV_RECV_FUNC_ID_MAX,

	GUOM0_TEST1 = 0,

	GUOM0_RECV_FUNC_ID_MAX,

	GUOM1_TEST1 = 0,

	GUOM1_RECV_FUNC_ID_MAX,

	GUOM2_TEST1 = 0,

	GUOM2_RECV_FUNC_ID_MAX,

	GUOM3_TEST1 = 0,

	GUOM3_RECV_FUNC_ID_MAX,

	GUOM4_TEST1 = 0,

	GUOM4_RECV_FUNC_ID_MAX,

	GUOM5_TEST1 = 0,

	GUOM5_RECV_FUNC_ID_MAX,

	CSHELL_TEST1 = 0,

	CSHELL_RECV_FUNC_ID_MAX,

    AC_PANRPC_ID = 0,

    AC_PANRPC_RECV_FUNC_ID_MAX,

	MCORE_CCORE_FUNC_TEST1 = 0,
	MCORE_CCORE_FUNC_TEST2,
	MCORE_CCORE_FUNC_HKADC = 2,
	MCU_CCORE_CPUFREQ = 3,
	MCU_CCORE_WSRC = 4,
	MCORE_CCORE_FUNC_WAKEUP = 5,
	MCORE_CCORE_FUNC_REGULATOR,
	MCORE_CCORE_FUNC_SIM0,
	MCORE_CCORE_FUNC_SIM1,
	MCORE_CCORE_FUNC_SOCP = 9,
	MCORE_CCORE_FUNC_UART,
	MCORE_CCORE_FUNC_TSENSOR,
	MCORE_CCORE_FUNC_PDLOCK,

	MCORE_CCORE_FUNC_ID_MAX,

	MCORE_ACORE_FUNC_TEST1 = 0,
	MCORE_ACORE_FUNC_TEST2,
	MCORE_ACORE_FUNC_HKADC,
	MCU_ACORE_CPUFREQ,
	MCU_ACORE_WSRC,
	NV_RECV_FUNC_AM,
	MCORE_ACORE_FUNC_TEMPERATURE,
	MCU_ACORE_RFILE,
	MCORE_ACORE_FUNC_WAKEUP,
	MCORE_ACORE_FUNC_DUMP,
	MCORE_ACORE_FUNC_RESET,
	MCORE_ACORE_FUNC_PM_OM,

	MCORE_ACORE_FUNC_ID_MAX,

	HIFI_TPHY_MSG_NRM = 0,
	HIFI_TPHY_MSG_URG,
	HIFI_TPHY_MSG_MAX,

	CCPU_HIFI_VOS_MSG_NRM = 0,
	CCPU_HIFI_VOS_MSG_URG,
	CCPU_HIFI_VOS_MSG_MAX,

	SEC_IFC_RECV_FUNC_MODULE_VERIFY = 0,

	SEC_IFC_RECV_FUNC_ID_MAX,

	SEC_VSIM_RECV_FUNC_TEST = 0,

	SEC_VSIM_RECV_FUNC_ID_MAX 

};

struct icc_channel_packet
{
	u32 channel_id;
	u32 len;
	u32 src_cpu_id;
	u32 seq_num;
	u32 need_responsed:1;
	u32 is_responsed:1;
	u32 reserved:30;
	s32 data;
	u32 timestamp;
	u32 task_id;
};

struct icc_channel_fifo
{
	u32 magic;
	u32 size;
	u32 write;
	u32 read;
	u8  data[4];
};

#define ICC_CHANNEL_PAYLOAD                        (sizeof(struct icc_channel_packet) + 4)
#define ICC_CHANNEL_ID_MAKEUP(channel_id, func_id) ((channel_id << 16) | (func_id))
#define SHM_ADDR_ICC                               (char *) ((unsigned long)SHM_BASE_ADDR + SHM_OFFSET_ICC)
#define SRAM_ADDR_ICC                              (char *) ((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_ICC)

typedef s32 (*read_cb_func)(u32 channel_id , u32 len, void* context);
typedef s32 (*write_cb_func)(u32 channel_id , void* context);

s32 bsp_icc_send(u32 cpuid,u32 channel_id,u8 *buffer,u32 data_len);

s32 bsp_icc_send_sync(u32 cpuid,u32 channel_id,u8 * data,u32 data_len,long timeout);

s32 bsp_icc_read(u32 channel_id,u8 * buf,u32 buf_len);

s32 bsp_icc_event_register(u32 channel_id, read_cb_func read_cb, void *read_context,
                                              write_cb_func write_cb, void *write_context);

s32 bsp_icc_event_unregister(u32 channel_id);

s32 bsp_icc_debug_register(u32 channel_id, FUNCPTR_1 debug_routine, int param);

s32 bsp_icc_init(void);
void bsp_icc_release(void);
s32 bsp_icc_suspend(void);

#define STRU_SIZE             (sizeof(struct icc_channel_fifo))
#define ICC_IFC_SIZE          (SZ_4K)
#define ICC_RFILE_SIZE        (SZ_4K)
#define ICC_NV_SIZE           (SZ_4K)
#define ICC_GUOM0_SIZE        (SZ_16K)
#define ICC_GUOM1_SIZE        (0)
#define ICC_GUOM2_SIZE        (0)
#define ICC_GUOM3_SIZE        (0)
#define ICC_GUOM4_SIZE        (SZ_128K)
#define ICC_GUOM5_SIZE        (0)
#define ICC_CSHELL_SIZE       (SZ_8K)
#define ICC_PANRPC_SIZE       (SZ_4K)
#define ICC_MCCORE_SIZE       (SZ_512)
#define ICC_MACORE_SIZE       (SZ_512)
#define ICC_HIFI_VOS_SIZE     (6 * 1024)
#define ICC_HIFI_TPHY_SIZE    (6 * 1024)
#define ICC_VT_VOIP_SIZE      (SZ_4K)

#define ICC_DBG_MSG_LEN_IN_DDR  (0x20)
#define ICC_DBG_MSG_ADDR_IN_DDR (char *) (((unsigned long)(SHM_ADDR_ICC) + 3) & ~3)
#define ADDR_IFC_SEND         (ICC_DBG_MSG_ADDR_IN_DDR + ICC_DBG_MSG_LEN_IN_DDR)
#define ADDR_IFC_RECV         (ADDR_IFC_SEND    + STRU_SIZE + ICC_IFC_SIZE)
#define ADDR_RFILE_SEND       (ADDR_IFC_RECV    + STRU_SIZE + ICC_IFC_SIZE)
#define ADDR_RFILE_RECV       (ADDR_RFILE_SEND  + STRU_SIZE + ICC_RFILE_SIZE)
#define ADDR_NV_SEND          (ADDR_RFILE_RECV  + STRU_SIZE + ICC_RFILE_SIZE)
#define ADDR_NV_RECV          (ADDR_NV_SEND     + STRU_SIZE + ICC_NV_SIZE)
#define ADDR_GUOM0_SEND       (ADDR_NV_RECV     + STRU_SIZE + ICC_NV_SIZE)
#define ADDR_GUOM0_RECV       (ADDR_GUOM0_SEND  + STRU_SIZE + ICC_GUOM0_SIZE)
#define ADDR_GUOM1_SEND       (ADDR_GUOM0_RECV  + STRU_SIZE + ICC_GUOM0_SIZE)
#define ADDR_GUOM1_RECV       (ADDR_GUOM1_SEND  + STRU_SIZE + ICC_GUOM1_SIZE)
#define ADDR_GUOM2_SEND       (ADDR_GUOM1_RECV  + STRU_SIZE + ICC_GUOM1_SIZE)
#define ADDR_GUOM2_RECV       (ADDR_GUOM2_SEND  + STRU_SIZE + ICC_GUOM2_SIZE)
#define ADDR_GUOM3_SEND       (ADDR_GUOM2_RECV  + STRU_SIZE + ICC_GUOM2_SIZE)
#define ADDR_GUOM3_RECV       (ADDR_GUOM3_SEND  + STRU_SIZE + ICC_GUOM3_SIZE)
#define ADDR_GUOM4_SEND       (ADDR_GUOM3_RECV  + STRU_SIZE + ICC_GUOM3_SIZE)
#define ADDR_GUOM4_RECV       (ADDR_GUOM4_SEND  + STRU_SIZE + ICC_GUOM4_SIZE)
#define ADDR_GUOM5_SEND       (ADDR_GUOM4_RECV  + STRU_SIZE + ICC_GUOM4_SIZE)
#define ADDR_GUOM5_RECV       (ADDR_GUOM5_SEND  + STRU_SIZE + ICC_GUOM5_SIZE)
#define ADDR_CSHELL_SEND      (ADDR_GUOM5_RECV  + STRU_SIZE + ICC_GUOM5_SIZE)
#define ADDR_CSHELL_RECV      (ADDR_CSHELL_SEND + STRU_SIZE + ICC_CSHELL_SIZE)
#define ADDR_PANRPC_SEND      (ADDR_CSHELL_RECV + STRU_SIZE + ICC_CSHELL_SIZE)
#define ADDR_PANRPC_RECV      (ADDR_PANRPC_SEND + STRU_SIZE + ICC_PANRPC_SIZE)

#ifdef SHM_SEC_BASE_ADDR
#define SHM_S_ADDR_ICC            (SHM_SEC_BASE_ADDR + SHM_OFFSET_SEC_ICC)
#define SHM_S_SIZE_ICC            (SHM_SIZE_SEC_ICC)
#else
#define SHM_S_ADDR_ICC            0
#define SHM_S_SIZE_ICC            0
#endif

#define ICC_DBG_MSG_LEN_IN_DDR_S  (0x20)
#define ICC_DBG_MSG_ADDR_IN_DDR_S (char *) (((unsigned long)(SHM_S_ADDR_ICC) + 3) & ~3)

#ifndef BSP_ICC_MCHANNEL_USE_LPM3TCM /* BALONGV7R2 */

#define ADDR_MCCORE_SEND      (SRAM_ADDR_ICC)
#else                          /* K3V3 */
#define ADDR_MCCORE_SEND      (ADDR_PANRPC_RECV + STRU_SIZE + ICC_PANRPC_SIZE)
#endif
#define ADDR_MCCORE_RECV      (ADDR_MCCORE_SEND + STRU_SIZE + ICC_MCCORE_SIZE)
#define ADDR_MACORE_SEND      (ADDR_MCCORE_RECV + STRU_SIZE + ICC_MCCORE_SIZE)
#define ADDR_MACORE_RECV      (ADDR_MACORE_SEND + STRU_SIZE + ICC_MACORE_SIZE)

#ifndef BSP_ICC_MCHANNEL_USE_LPM3TCM
#define ADDR_HIFI_VOS_MSG_SEND      (ADDR_PANRPC_RECV + STRU_SIZE + ICC_PANRPC_SIZE)
#else                          
#define ADDR_HIFI_VOS_MSG_SEND      (ADDR_MACORE_RECV + STRU_SIZE + ICC_MACORE_SIZE)
#endif
#define ADDR_HIFI_VOS_MSG_RECV      (ADDR_HIFI_VOS_MSG_SEND + STRU_SIZE + ICC_HIFI_VOS_SIZE)
#define ADDR_HIFI_TPHY_MSG_SEND      (ADDR_HIFI_VOS_MSG_RECV + STRU_SIZE + ICC_HIFI_VOS_SIZE)
#define ADDR_HIFI_TPHY_MSG_RECV      (ADDR_HIFI_TPHY_MSG_SEND + STRU_SIZE + ICC_HIFI_TPHY_SIZE)

#define ADDR_VT_VOIP_CCORE_RECV_ACORE_SEND       (ADDR_HIFI_TPHY_MSG_RECV + STRU_SIZE + ICC_HIFI_TPHY_SIZE)
#define ADDR_VT_VOIP_CCORE_SEND_ACORE_RECV       (ADDR_VT_VOIP_CCORE_RECV_ACORE_SEND + STRU_SIZE + ICC_VT_VOIP_SIZE)


#ifdef __cplusplus /* __cplusplus */
}
#endif /* __cplusplus */

#endif    /*  __BSP_ICC_H__ */
