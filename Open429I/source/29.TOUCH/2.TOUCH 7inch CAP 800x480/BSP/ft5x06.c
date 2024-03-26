/**
  ******************************************************************************
  * @file    ft6x06.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    03-August-2015
  * @brief   This file provides a set of functions needed to manage the FT6X06
  *          IO Expander devices.
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

/* Includes ------------------------------------------------------------------*/
#include "ft5x06.h"
#include "TS_I2C.h"
#include "stm32f4xx_hal.h"
#include "stm324x9i_lcd.h"
/** @addtogroup BSP
  * @{
  */
	
uint8_t RegBuf[31];
TS_StateTypeDef  TS_State;
uint8_t TS_flag ;

/** @addtogroup Component
  * @{
  */

/** @defgroup FT6X06
  * @{
  */

/* Private typedef -----------------------------------------------------------*/



/**
  * @}
  */

/** @defgroup ft6x06_Private_Functions ft6x06 Private Functions
  * @{
  */

/**
  * @brief  Initialize the ft5x06 communication bus
  *         from MCU to FT5206 : ie I2C channel initialization (if required).
  * @param  DeviceAddr: Device address on communication Bus (I2C slave address of FT6206).
  * @retval None
  */

void ft5x06_Init()
{  

	I2C_Init();
//	ft5x06_ReadID();
}


/**
  * @brief  Read the ft5x06 device ID, pre initialize I2C in case of need to be
  *         able to read the FT5206 device ID, and verify this is a FT6206.
  * @param  DeviceAddr: I2C FT6x06 Slave address.
  * @retval The Device ID (two bytes).
  */
uint16_t ft5x06_ReadID()
{
	uint8_t value = 0;
  I2C_ReadReg(TS_I2C_ADDR,FT5206_CHIP_ID_REG,&value, 1);
	return value;
}


void ft5x06_TS_GetState(TS_StateTypeDef *TS_State)
{
//	HAL_I2C_Mem_Read(&hi2c_tc, TS_I2C_ADDR_READ, 0,I2C_MEMADD_SIZE_8BIT, RegBuf, sizeof(RegBuf), 1000);
	I2C_ReadReg(TS_I2C_ADDR,0,RegBuf,sizeof(RegBuf));
	TS_State->touchDetected = RegBuf[0x02] & 0x0F;
	TS_State->gestureId = RegBuf[0x01];

	//Touch point 1 coordinates
	TS_State->touchX[0] = (((RegBuf[0x03] & 0x0F) << 8) + RegBuf[0x04]);
	TS_State->touchY[0] = FT5x06_MAX_HEIGHT - (((RegBuf[0x05] & 0x0F) << 8) + RegBuf[0x06]) - 1;
	TS_State->touchEventId[0] = RegBuf[0x03] & 0xF0;	

	//Touch point 2 coordinates
	TS_State->touchX[1] = (((RegBuf[0x09] & 0x0F) << 8) + RegBuf[0x0A]);
	TS_State->touchY[1] = FT5x06_MAX_HEIGHT - (((RegBuf[0x0B] & 0x0F) << 8) + RegBuf[0x0C]) - 1;
	TS_State->touchEventId[1] = RegBuf[0x09] & 0xF0;	

	//Touch point 3 coordinates
	TS_State->touchX[2] = (((RegBuf[0x0F] & 0x0F) << 8) + RegBuf[0x10]);
	TS_State->touchY[2] = FT5x06_MAX_HEIGHT - (((RegBuf[0x11] & 0x0F) << 8) + RegBuf[0x12]) - 1;
	TS_State->touchEventId[2] = RegBuf[0x0F] & 0xF0;	

	//Touch point 4 coordinates
	TS_State->touchX[3] = (((RegBuf[0x15] & 0x0F) << 8) + RegBuf[0x16]);
	TS_State->touchY[3] = FT5x06_MAX_HEIGHT - (((RegBuf[0x17] & 0x0F) << 8) + RegBuf[0x18]) - 1;
	TS_State->touchEventId[3] = RegBuf[0x15] & 0xF0;	

	//Touch point 5 coordinates
	TS_State->touchX[4] = (((RegBuf[0x1B] & 0x0F) << 8) + RegBuf[0x1C]);
	TS_State->touchY[4] = FT5x06_MAX_HEIGHT - (((RegBuf[0x1D] & 0x0F) << 8) + RegBuf[0x1E]) - 1;
	TS_State->touchEventId[4] = RegBuf[0x1B] & 0xF0;

}

/**
  * @}
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == GPIO_PIN_4)
	{
		TS_flag = 1;
		printf("ok!\r\n");
	}
}
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
