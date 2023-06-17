/******************************************************************************

                  ???????? (C), 2001-2011, ????????????????

 ******************************************************************************
  ?? ?? ??   : SdioInterface.h
  ?? ?? ??   : ????
  ??    ??   : ????/l60609
  ????????   : 2014??01??26??
  ????????   :
  ????????   : SDIO??????????????
  ????????   :
  ????????   :
  1.??    ??   : 2014??01??26??
    ??    ??   : ????/l60609
    ????????   : ????????

******************************************************************************/

#ifndef __SDIOINTERFACE_H__
#define __SDIOINTERFACE_H__

/*****************************************************************************
  1 ??????????
*****************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 ??????
*****************************************************************************/

#define SDIO_OK                         (0)
#define SDIO_ERR                        (1)

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


/*****************************************************************************
  8 UNION????
*****************************************************************************/


/*****************************************************************************
  9 OTHERS????
*****************************************************************************/


/*****************************************************************************
   10 ????????
*****************************************************************************/
/*****************************************************************************
 SDIO????????????????????????????????????????????????
 ??????????????????????????????????????
*****************************************************************************/
unsigned long SDIO_UL_SendPacket(
    struct sk_buff                     *pstData,
    unsigned char                       ucPDNId
);


typedef unsigned long (*RCV_C_DL_DATA_FUNC)(unsigned char ucPDNId, struct sk_buff *pstData);

/*****************************************************************************
  SDIO????????????????????????????????????????
*****************************************************************************/
unsigned long SDIO_DL_RegDataCallback(unsigned char ucPDNId, RCV_C_DL_DATA_FUNC pFunc);

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




