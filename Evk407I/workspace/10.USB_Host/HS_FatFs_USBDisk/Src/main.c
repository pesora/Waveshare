/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  *
  * Copyright (c) 2017 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_hal.h"
#include "fatfs.h"
#include "usb_host.h"
#include "gpio.h"
#include "fsmc.h"

/* USER CODE BEGIN Includes */
#include "stm32_lcd_bsp.h"
#include "lcd_log.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
FATFS USBDISKFatFs;           /* File system object for USB disk logical drive */
FIL MyFile;                   /* File object */
extern USBH_HandleTypeDef hUsbHostHS;
extern ApplicationTypeDef Appli_state;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void Error_Handler(void);
void MX_USB_HOST_Process(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
void MSC_Application(void);
/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_FSMC_Init();
  MX_FATFS_Init();
  MX_USB_HOST_Init();

  /* USER CODE BEGIN 2 */
  BSP_LCD_Init();
  /* Initialize LCD Log module */
  LCD_LOG_Init();
  /* Show Header and Footer texts */
  LCD_LOG_SetHeader((uint8_t *)"HS FatFs USB Disk Example");
  LCD_LOG_SetFooter((uint8_t *)"Copyright(c) Waveshare");

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  /* USER CODE END WHILE */
    MX_USB_HOST_Process();

  /* USER CODE BEGIN 3 */
    /* Mass Storage Application State Machine */
    switch(Appli_state)
    {
      /**
        * The generated code from STM32CubeMX has two "confusing" application states 
        * APPLICATION_START on HOST_USER_CONNECTION and APPLICATION_READY on HOST_USER_CLASS_ACTIVE. 
        * Any FatFs commands should be executed after APPLICATION_STATE_READY is reached."
        */
      case APPLICATION_READY:
        MSC_Application();
        Appli_state = APPLICATION_IDLE;
        break;

      case APPLICATION_IDLE:
      default:
        break;      
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

    /**Configure the main internal regulator output voltage 
    */
  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */
/**
  * @brief  Main routine for Mass Storage Class
  * @param  None
  * @retval None
  */
void MSC_Application(void)
{
  /* FatFs function common result code description: */
    /*  FR_OK = 0,                (0) Succeeded */
    /*  FR_DISK_ERR,              (1) A hard error occurred in the low level disk I/O layer */
    /*  FR_INT_ERR,               (2) Assertion failed */
    /*  FR_NOT_READY,             (3) The physical drive cannot work */
    /*  FR_NO_FILE,               (4) Could not find the file */
    /*  FR_NO_PATH,               (5) Could not find the path */
    /*  FR_INVALID_NAME,          (6) The path name format is invalid */
    /*  FR_DENIED,                (7) Access denied due to prohibited access or directory full */
    /*  FR_EXIST,                 (8) Access denied due to prohibited access */
    /*  FR_INVALID_OBJECT,        (9) The file/directory object is invalid */
    /*  FR_WRITE_PROTECTED,       (10) The physical drive is write protected */
    /*  FR_INVALID_DRIVE,         (11) The logical drive number is invalid */
    /*  FR_NOT_ENABLED,           (12) The volume has no work area */
    /*  FR_NO_FILESYSTEM,         (13) There is no valid FAT volume */
    /*  FR_MKFS_ABORTED,          (14) The f_mkfs() aborted due to any parameter error */
    /*  FR_TIMEOUT,               (15) Could not get a grant to access the volume within defined period */
    /*  FR_LOCKED,                (16) The operation is rejected according to thex file sharing policy */
    /*  FR_NOT_ENOUGH_CORE,       (17) LFN working buffer could not be allocated */
    /*  FR_TOO_MANY_OPEN_FILES,   (18) Number of open files > _FS_SHARE */
    /*  FR_INVALID_PARAMETER      (19) Given parameter is invalid */

  FRESULT res;                                          /* FatFs function common result code */
  uint32_t byteswritten, bytesread;                     /* File write/read counts */
  uint8_t wtext[] = "Hello World!";                     /* File write buffer */
  uint8_t rtext[100];                                   /* File read buffer */
  
  /* Register the file system object to the FatFs module */
  res = f_mount(&USBDISKFatFs, (TCHAR const*)USBH_Path, 0);
  if(res != FR_OK)  
  {
    /* FatFs Initialization Error */
    USBH_UsrLog("f_mount error: %d", res);
    Error_Handler();
  } 

  USBH_UsrLog("create the file in: %s", USBH_Path);
  /* Create and Open a new text file object with write access */
  res = f_open(&MyFile, "hello.txt", FA_CREATE_ALWAYS | FA_WRITE);
  if(res != FR_OK) 
  {
    /* 'hello.txt' file Open for write Error */
    USBH_UsrLog("f_open with write access error: %d", res);
    Error_Handler();
  }
  /* Write data to the text file */
  res = f_write(&MyFile, wtext, sizeof(wtext), (void *)&byteswritten);
  if((byteswritten == 0) || (res != FR_OK)) 
  {
    /* 'hello.txt' file Write or EOF Error */
    USBH_UsrLog("file write or EOF error: %d", res);
    Error_Handler();
  }

  /* Close the open text file */
  f_close(&MyFile);
  
  /* Open the text file object with read access */
  res = f_open(&MyFile, "hello.txt", FA_READ);
  if(res != FR_OK) 
  {
    /* 'hello.txt' file Open for read Error */
    USBH_UsrLog("f_open with read access error: %d", res);
    Error_Handler();
  }
 
  /* Read data from the text file */
  res = f_read(&MyFile, rtext, sizeof(rtext), (void *)&bytesread);
  if((bytesread == 0) || (res != FR_OK)) 
  {
    /* 'hello.txt' file Read or EOF Error */
    USBH_UsrLog("f_read error: %d", res);
    Error_Handler();
  }
 
  /* Close the open text file */
  f_close(&MyFile);
  
  /* Compare read data with the expected data */
  if((bytesread != byteswritten))
  {                
    /* Read data is different from the expected data */
    USBH_UsrLog("file doesn't match");
    Error_Handler();
  }

  /* Success of the demo: no error occurrence */
  USBH_UsrLog("hello.txt was created into the disk");
  
  /* Unlink the USB disk I/O driver */
  FATFS_UnLinkDriver(USBH_Path);
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler */ 
}

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
