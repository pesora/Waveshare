/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  *
  * COPYRIGHT(c) 2015 STMicroelectronics
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
#include "stm32f4xx_hal.h"
#include "dma.h"
#include "dma2d.h"
#include "ltdc.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"
#include "fmc.h"

/* USER CODE BEGIN Includes */
#include "stm324x9i_sdram.h"
#include "stm324x9i_lcd.h"
#include "TouchPanel.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */
	uint16_t linenum = 0;
  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_DMA2D_Init();
  MX_FMC_Init();
  MX_LTDC_Init();
  MX_SPI2_Init();
  MX_USART1_UART_Init();

  /* USER CODE BEGIN 2 */
	printf("\r\n SDRAM example !!!\r\n");
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_4,GPIO_PIN_SET);
	
	  /*##-1- Configure the SDRAM device #########################################*/
  /* Program the SDRAM external device */
  BSP_SDRAM_Init();   
  
	/* Initialize the LCD */
  BSP_LCD_Init();
  
  /* Set Foreground Layer */
  BSP_LCD_SelectLayer(1);
  /* Clear the LCD Foreground layer */
//  BSP_LCD_Clear(LCD_COLOR_WHITE);
  BSP_LCD_SetLayerVisible(1, DISABLE);
  /* Set Foreground Layer */
  BSP_LCD_SelectLayer(0);
  
  /* Enable the LCD */
  BSP_LCD_DisplayOn();
  
  /* Clear the LCD Background layer */

  /* Touch Panel configuration */
//	TP_Init();
  TouchPanel_Calibrate(); 
 	BSP_LCD_Clear(LCD_COLOR_WHITE);
	BSP_LCD_SetFont(&Font12);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK); 
	BSP_LCD_DisplayStringAt(0,240, (uint8_t*)"Touch Panel Paint   ",RIGHT_MODE);
	BSP_LCD_DisplayStringAt(0,255, (uint8_t*)"Example             ",RIGHT_MODE);

	BSP_LCD_SetTextColor(LCD_COLOR_RED); 
	BSP_LCD_FillRect(5, 238, 30, 30);
	BSP_LCD_SetTextColor(LCD_COLOR_BLUE); 
	BSP_LCD_FillRect(40, 238, 30, 30);
	BSP_LCD_SetTextColor(LCD_COLOR_GREEN); 
	BSP_LCD_FillRect(75, 238, 30, 30);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK); 
	BSP_LCD_FillRect(110, 238, 30, 30);	
	BSP_LCD_SetTextColor(LCD_COLOR_MAGENTA); 
	BSP_LCD_FillRect(145, 238, 30, 30);
	BSP_LCD_SetTextColor(LCD_COLOR_ORANGE); 
	BSP_LCD_FillRect(180, 238, 30, 30);
	BSP_LCD_SetTextColor(LCD_COLOR_CYAN); 
	BSP_LCD_FillRect(215, 238, 30, 30);
	BSP_LCD_SetTextColor(LCD_COLOR_YELLOW); 
	BSP_LCD_FillRect(250, 238, 30, 30);
	
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK); 
	
	
	BSP_LCD_SetFont(&Font24);
	BSP_LCD_DisplayChar(290, 240, 'C');
	BSP_LCD_DrawHLine(  0, 232, 480);
 
	BSP_LCD_DrawVLine(  1, 232,  36);
	BSP_LCD_DrawVLine( 37, 232,  36);
	BSP_LCD_DrawVLine( 72, 232,  36);
	BSP_LCD_DrawVLine(107, 232,  36);
	BSP_LCD_DrawVLine(142, 232,  36);
	
	BSP_LCD_DrawVLine(177, 232,  36);
	BSP_LCD_DrawVLine(212, 232,  36);
	BSP_LCD_DrawVLine(247, 232,  36);
	BSP_LCD_DrawVLine(282, 232,  36);
	BSP_LCD_DrawVLine(317, 232,  36);
	
	BSP_LCD_DrawHLine(  1, 269, 480);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
		getDisplayPoint(&display, Read_Ads7846(), &matrix );		
	  if(((display.y < 230) && (display.y >= 2)))
    {
			if((display.x >= 478) || (display.x < 2))
      {}     
      else
      {
        BSP_LCD_FillCircle(display.x, display.y, 2);
      }
    }
    else if ((display.y <= 270) && (display.y >= 230) && (display.x >= 180) && (display.x <= 210))
    {
      BSP_LCD_SetTextColor(LCD_COLOR_ORANGE);
    }
    else if ((display.y <= 270) && (display.y >= 230) && (display.x >= 215) && (display.x <= 245))
    {
      BSP_LCD_SetTextColor(LCD_COLOR_CYAN); 
    }
    else if ((display.y <= 270) && (display.y >= 230) && (display.x >= 250) && (display.x <= 280))
    {
      BSP_LCD_SetTextColor(LCD_COLOR_YELLOW); 
    }      
    else if ((display.y <= 270) && (display.y >= 230) && (display.x >= 5) && (display.x <= 35))
    {
      BSP_LCD_SetTextColor(LCD_COLOR_RED);
    }
    else if ((display.y <= 270) && (display.y >= 230) && (display.x >= 40) && (display.x <= 70))
    {
      BSP_LCD_SetTextColor(LCD_COLOR_BLUE); 
    }
    else if ((display.y <= 270) && (display.y >= 230) && (display.x >= 75) && (display.x <= 105))
    {
      BSP_LCD_SetTextColor(LCD_COLOR_GREEN); 
    }
    else if ((display.y <= 270) && (display.y >= 230) && (display.x >= 110) && (display.x <= 140))
    {
      BSP_LCD_SetTextColor(LCD_COLOR_BLACK); 
    }
    else if ((display.y <= 270) && (display.y >= 230) && (display.x >= 145) && (display.x <= 175))
    {
      BSP_LCD_SetTextColor(LCD_COLOR_MAGENTA); 
    }
    else if ((display.y <= 270) && (display.y >= 230) && (display.x >= 285) && (display.x <= 315))
    {
      BSP_LCD_SetFont(&Font8);
      for(linenum = 0; linenum < 29; linenum++)
      {
        BSP_LCD_ClearStringLine(linenum);
      }
    }
    else
    {
    }
  }
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;

  __PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 360;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  HAL_PWREx_ActivateOverDrive();

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_PCLK1
                              |RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);

  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
  PeriphClkInitStruct.PLLSAI.PLLSAIN = 192;
  PeriphClkInitStruct.PLLSAI.PLLSAIR = 3;
  PeriphClkInitStruct.PLLSAIDivR = RCC_PLLSAIDIVR_4;
  HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
