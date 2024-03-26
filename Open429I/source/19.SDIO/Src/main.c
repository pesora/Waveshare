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
#include "sdio.h"
#include "usart.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */
#include <string.h>
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
HAL_SD_ErrorTypedef Status;
uint32_t Buffer_Tx[512/4], Buffer_Rx[512/4];
/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
	
/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */
	uint32_t i;
  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_SDIO_SD_Init();
  MX_USART1_UART_Init();

  /* USER CODE BEGIN 2 */
	printf(" Warning: this program may erase all the TF card data. \r\n Make sure you have backed up. Press 'y' to continue.\r\n");
	Status = HAL_SD_Init(&hsd, &SDCardInfo);
	if (Status == SD_OK)
  {				                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 +                    
    printf("\r\n Initialize SD card successfully!\r\n\r\n");
		printf(" SD card information! \r\n");
		printf(" CardCapacity  : %llu \r\n",SDCardInfo.CardCapacity );
		printf(" CardBlockSize : %d \r\n",SDCardInfo.CardBlockSize);
		printf(" RCA           : %d \r\n",SDCardInfo.RCA);
		printf(" CardType      : %d \r\n",SDCardInfo.CardType);
  }
	else
	{
		printf("\r\n Initialize SD card fail!\r\n");
	}
	
	Status = HAL_SD_WideBusOperation_Config(&hsd,SDIO_BUS_WIDE_4B);
	if (Status == SD_OK)
    printf("\r\n Enable wide bus operation successfully!\r\n");
	else 
		printf("\r\n Enable wide bus operation fail!\r\n");
	
	/*------------------- Block Write --------------------------*/
	memset(Buffer_Tx,0x15,sizeof(Buffer_Tx));
	
	Status = HAL_SD_WriteBlocks_DMA(&hsd, Buffer_Tx, 0, 512, 1);
//	Status = HAL_SD_CheckWriteOperation(&hsd, 0xFF);
	if (Status == SD_OK)
	{
    printf("\r\n Write block successfully!\r\n");
		for(i=0;i<sizeof(Buffer_Tx)>>2;i++)
		{
			printf("%02x:0x%08x ",i,Buffer_Tx[i]);
		}
		printf("\r\n");
	}
	else 
		printf("\r\n Write block fail!\r\n");
	
	/*------------------- Block Read --------------------------*/
	Status = HAL_SD_ReadBlocks_DMA(&hsd, Buffer_Rx, 0, 512, 1);
//	Status = HAL_SD_CheckReadOperation(&hsd, 0xFF);
	if (Status == SD_OK)
	{
    printf("\r\n Read block successfully!\r\n");
		for(i=0;i<sizeof(Buffer_Rx)>>2;i++)
		{
			printf("%02x:0x%08x ",i,Buffer_Rx[i]);
		}
		printf("\r\n");
	}
	else 
		printf("\r\n Read block fail!\r\n");
	
	/*------------------- Block Erase -------------------------------*/
	Status = HAL_SD_Erase(&hsd, 0, 512);
	if (Status == SD_OK)
    printf("\r\n Erase block successfully!\r\n");
	else 
		printf("\r\n Erase block fail!\r\n");
	
	/*------------------- Block Read --------------------------*/
	Status = HAL_SD_ReadBlocks_DMA(&hsd, Buffer_Rx, 0, 512, 1);
//	Status = HAL_SD_CheckReadOperation(&hsd, 0xFF);
	if (Status == SD_OK)
	{
    printf("\r\n Read block successfully!\r\n");
		for(i=0;i<sizeof(Buffer_Rx)>>2;i++)
		{
			printf("%02x:0x%08x ",i,Buffer_Rx[i]);
		}
		printf("\r\n");
	}
	else 
		printf("\r\n Read block fail!\r\n");

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
		
  }
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

  __PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_PCLK1
                              |RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);

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