/**
 ******************************************************************************
 * @file    ft6x06.h
 * @author  MCD Application Team
  * @version V1.0.0
  * @date    03-August-2015
 * @brief   This file contains all the functions prototypes for the
 *          ft6x06.c IO expander driver.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FT5X06_H
#define __FT5X06_H

#ifdef __cplusplus
extern "C" {
#endif
  
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Macros --------------------------------------------------------------------*/

/** @typedef ft6x06_handle_TypeDef
 *  ft6x06 Handle definition.
 */


  /** @addtogroup BSP
   * @{
   */

  /** @addtogroup Component
   * @{
   */

  /** @defgroup FT6X06
   * @{
   */

  /* Exported types ------------------------------------------------------------*/

  /** @defgroup FT6X06_Exported_Types
   * @{
   */

  /* Exported constants --------------------------------------------------------*/

  /** @defgroup FT6X06_Exported_Constants
   * @{
   */
/**
  * @brief TouchScreen FT6206 Slave I2C address
  */
#define TS_I2C_ADDR                   ((uint16_t)0x70)     

  /* Maximum border values of the touchscreen pad */
#define  FT5x06_MAX_WIDTH              ((uint16_t)800)     /* Touchscreen pad max width   */
#define  FT5x06_MAX_HEIGHT             ((uint16_t)480)     /* Touchscreen pad max height  */

  /* Possible values of driver functions return status */
#define FT5206_STATUS_OK                0
#define FT5206_STATUS_NOT_OK            1


  /* Max detectable simultaneous touches */
#define TS_MAX_NB_TOUCH                 5

  /**
   * @brief : Definitions for FT6206 I2C register addresses on 8 bit
   **/

  /* Current mode register of the FT6206 (R/W) */
#define FT5206_DEV_MODE_REG             0x00

  /* Gesture ID register */
#define FT5206_GEST_ID_REG              0x01

  /* Possible values of FT6206_GEST_ID_REG */
#define FT5206_GEST_ID_NO_GESTURE       0x00
#define FT5206_GEST_ID_MOVE_UP          0x10
#define FT5206_GEST_ID_MOVE_RIGHT       0x14
#define FT5206_GEST_ID_MOVE_DOWN        0x18
#define FT5206_GEST_ID_MOVE_LEFT        0x1C
#define FT5206_GEST_ID_ZOOM_IN          0x48
#define FT5206_GEST_ID_ZOOM_OUT         0x49

  /* Touch Data Status register : gives number of active touch points (0..2) */
#define FT5206_TD_STAT_REG              0x02

  /* Values Pn_XH and Pn_YH related */
#define FT5206_TOUCH_EVT_FLAG_PRESS_DOWN 0x00
#define FT5206_TOUCH_EVT_FLAG_LIFT_UP    0x01
#define FT5206_TOUCH_EVT_FLAG_CONTACT    0x02
#define FT5206_TOUCH_EVT_FLAG_NO_EVENT   0x03


#define FT5206_P1_XH_REG               0x03
#define FT5206_P1_XL_REG               0x04
#define FT5206_P1_YH_REG               0x05
#define FT5206_P1_YL_REG               0x06

#define FT5206_P2_XH_REG               0x09
#define FT5206_P2_XL_REG               0x0A
#define FT5206_P2_YH_REG               0x0B
#define FT5206_P2_YL_REG               0x0C

#define FT5206_P3_XH_REG               0x0F
#define FT5206_P3_XL_REG               0x10
#define FT5206_P3_YH_REG               0x11
#define FT5206_P3_YL_REG               0x12

#define FT5206_P4_XH_REG               0x15
#define FT5206_P4_XL_REG               0x16
#define FT5206_P4_YH_REG               0x17
#define FT5206_P4_YL_REG               0x18

#define FT5206_P5_XH_REG               0x1B
#define FT5206_P5_XL_REG               0x1C
#define FT5206_P5_YH_REG               0x1D
#define FT5206_P5_YL_REG               0x1E


  /* FT6206 Chip identification register */
#define FT5206_CHIP_ID_REG              0xA8

  /*  Possible values of FT6206_CHIP_ID_REG */
#define FT5206_ID_VALUE                 0x79

typedef struct
{
  uint8_t  touchDetected;                /*!< Total number of active touches detected at last scan */
  uint16_t touchX[TS_MAX_NB_TOUCH];      /*!< Touch X[0], X[1] coordinates on 12 bits */
  uint16_t touchY[TS_MAX_NB_TOUCH];      /*!< Touch Y[0], Y[1] coordinates on 12 bits */
  uint8_t  touchEventId[TS_MAX_NB_TOUCH];     /*!< Touch_EventId[0], Touch_EventId[1] : take value of type @ref TS_TouchEventTypeDef */
	uint32_t gestureId; /*!< type of gesture detected : take value of type @ref TS_GestureIdTypeDef */

} TS_StateTypeDef;

void ft5x06_Init(void);
uint16_t ft5x06_ReadID(void);
void ft5x06_TS_GetState(TS_StateTypeDef *TS_State);
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */
#endif
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
