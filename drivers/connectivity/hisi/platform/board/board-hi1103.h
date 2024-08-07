#ifndef __BOARD_HI1103_H__
#define __BOARD_HI1103_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif

/*****************************************************************************
  1 Include other Head file
*****************************************************************************/

/*****************************************************************************
  2 Define macro
*****************************************************************************/
#define BOARD_VERSION_NAME_HI1103           "hi1103"

/*****************************************************************************
  4 EXTERN VARIABLE
*****************************************************************************/

/*****************************************************************************
  5 EXTERN FUNCTION
*****************************************************************************/
extern int hi1103_get_board_gpio(void);
extern void hi1103_free_board_power_gpio(void);
extern int hi1103_board_wakeup_gpio_init(void);
extern void hi1103_free_board_wakeup_gpio(void);

#ifdef __cplusplus
    #if __cplusplus
            }
    #endif
#endif

#endif

