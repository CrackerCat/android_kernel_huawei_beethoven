/******************************************************************************

                  ???????? (C), 2001-2011, ????????????????

 ******************************************************************************
  ?? ?? ??   : errlog_cfg.h
  ?? ?? ??   : ????
  ??    ??   : d00212987
  ????????   : 2016??3??7??
  ????????   :
  ????????   : errlog_cfg.c ????????
  ????????   :
  ????????   :
  1.??    ??   : 2016??3??7??
    ??    ??   : d00212987
    ????????   : ????????

******************************************************************************/
#ifndef __ERRLOG_CFG_H__
#define __ERRLOG_CFG_H__

/*****************************************************************************
  1 ??????????????
*****************************************************************************/
#include "vos.h"
#include "product_config.h"
#include "errlog_faultiddef.h"
#include "cttf_errlog_cfg.h"
#include "nas_errlog_cfg.h"
#include "cas_errlog_cfg.h"
#include "csdr_errlog_cfg.h"
#include "cproc_errlog_cfg.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 ??????
*****************************************************************************/
#define   FAULT_ID_CONTAIN_ALARM_ID_MAX_NUM   (256) /* ERRLOG ????????faultid????256??alarm_id */
#define   ERR_LOG_PID_MAX_NUM                 (256) /* ERRLOG ????256??PID */


/*****************************************************************************
  3 ????????
*****************************************************************************/


/*****************************************************************************
  4 ????????????
*****************************************************************************/


/*****************************************************************************
  5 ??????????
*****************************************************************************/


/*****************************************************************************
  6 ????????
*****************************************************************************/


/*****************************************************************************
  7 STRUCT????
*****************************************************************************/

typedef struct
{
    VOS_UINT32                            ulPid;
    VOS_UINT32                            ulAlarmID;
}ERR_LOG_ALARM_STRU;

/*****************************************************************************
  8 UNION????
*****************************************************************************/


/*****************************************************************************
  9 OTHERS????
*****************************************************************************/


/*****************************************************************************
  10 ????????
*****************************************************************************/

extern VOS_INT32 ErrLog_GetErrlogPid(
           VOS_UINT32                          ulModemId,
           VOS_UINT32                         *PaulPidArray,
           VOS_UINT32                         *pulPidNum
       );
extern VOS_INT32 ErrLog_GetErrReptAddrAndSize(
           VOS_UINT32                          ulModemId,
           VOS_UINT_PTR                       *pulErrLogAddr,
           VOS_UINT32                         *pulsize
       );
extern VOS_INT32 ErrLog_GetPidAndAlarmId(
           VOS_UINT32                          ulModemId,
           VOS_UINT32                          ulFaultId,
           ERR_LOG_ALARM_STRU                 *paustAlarmArray,
           VOS_UINT32                         *pulAlarmNum
       );



#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
