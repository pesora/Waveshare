/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  *
  * COPYRIGHT(c) 2016 STMicroelectronics
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
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

/* USER CODE BEGIN Includes */     
#include "gpio.h"
/* USER CODE END Includes */

/* Variables -----------------------------------------------------------------*/
osThreadId LED1Handle;
osThreadId LED2Handle;
osThreadId SIGNAL_GENHandle;

/* USER CODE BEGIN Variables */
#define BIT_0	( 1 << 0 )
#define BIT_1	( 1 << 1 )
#define BIT_2	( 1 << 2 )
/* USER CODE END Variables */

/* Function prototypes -------------------------------------------------------*/
void LED1_Thread1(void const * argument);
void LED2_Thread2(void const * argument);
void Signal_Gen_Thread(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

/* Hook prototypes */

/* Init FreeRTOS */

void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the thread(s) */
  /* definition and creation of LED1 */
  osThreadDef(LED1, LED1_Thread1, osPriorityNormal, 0, 128);
  LED1Handle = osThreadCreate(osThread(LED1), NULL);

  /* definition and creation of LED2 */
  osThreadDef(LED2, LED2_Thread2, osPriorityIdle, 0, 128);
  LED2Handle = osThreadCreate(osThread(LED2), NULL);

  /* definition and creation of SIGNAL_GEN */
  osThreadDef(SIGNAL_GEN, Signal_Gen_Thread, osPriorityIdle, 0, 128);
  SIGNAL_GENHandle = osThreadCreate(osThread(SIGNAL_GEN), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
}

/* LED1_Thread1 function */
void LED1_Thread1(void const * argument)
{

  /* USER CODE BEGIN LED1_Thread1 */
	(void) argument;
  osEvent event;
  /* Infinite loop */
  for(;;)
  {
    event = osSignalWait( BIT_0, osWaitForever);
    if(event.value.signals == BIT_0)
    {
      BSP_LED_Toggle(LED1);
    }
  }
  /* USER CODE END LED1_Thread1 */
}

/* LED2_Thread2 function */
void LED2_Thread2(void const * argument)
{
  /* USER CODE BEGIN LED2_Thread2 */
	(void) argument;
  osEvent event;
  /* Infinite loop */
  for(;;)
  {
    event = osSignalWait( BIT_1 | BIT_2, osWaitForever);
    if(event.value.signals == (BIT_1 | BIT_2))
    {
      BSP_LED_Toggle(LED2);
    }
  }
  /* USER CODE END LED2_Thread2 */
}

/* Signal_Gen_Thread function */
void Signal_Gen_Thread(void const * argument)
{
  /* USER CODE BEGIN Signal_Gen_Thread */
	(void) argument;
  /* Infinite loop */
  for(;;)
  {
    osSignalSet( LED1Handle, BIT_0 );
    osDelay(500);
    osSignalSet( LED2Handle, BIT_1 | BIT_2 );
    osDelay(500);     
  }
  /* USER CODE END Signal_Gen_Thread */
}

/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
