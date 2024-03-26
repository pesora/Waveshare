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
osThreadId SEM_Thread1Handle;
osThreadId SEM_Thread2Handle;
osSemaphoreId SEMHandle;

/* USER CODE BEGIN Variables */

/* USER CODE END Variables */

/* Function prototypes -------------------------------------------------------*/
void SemaphoreThread1(void const * argument);
void SemaphoreThread2(void const * argument);

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

  /* Create the semaphores(s) */
  /* definition and creation of SEM */
  osSemaphoreDef(SEM);
  SEMHandle = osSemaphoreCreate(osSemaphore(SEM), 1);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the thread(s) */
  /* definition and creation of SEM_Thread1 */
  osThreadDef(SEM_Thread1, SemaphoreThread1, osPriorityNormal, 0, 128);
  SEM_Thread1Handle = osThreadCreate(osThread(SEM_Thread1), NULL);

  /* definition and creation of SEM_Thread2 */
  osThreadDef(SEM_Thread2, SemaphoreThread2, osPriorityIdle, 0, 128);
  SEM_Thread2Handle = osThreadCreate(osThread(SEM_Thread2), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
}

/* SemaphoreThread1 function */
void SemaphoreThread1(void const * argument)
{

  /* USER CODE BEGIN SemaphoreThread1 */
	uint32_t count = 0;
  /* Infinite loop */
  for(;;)
  {
		if (SEMHandle != NULL)
		{
      /* Try to obtain the semaphore. */
      if(osSemaphoreWait(SEMHandle , 100) == osOK)
      {
        count = osKernelSysTick() + 5000;
        
        while (count >= osKernelSysTick())
        {
          /* Toggle LED1 */
          BSP_LED_Toggle(LED1);
          
          /* Delay 200ms */
          osDelay(200);
        }
        
        /* Turn off LED1 */
        BSP_LED_Off(LED1);
        
        /* Release the semaphore */
        osSemaphoreRelease(SEMHandle);
        
        /* Suspend ourselves to execute thread 2 (lower priority)  */
        osThreadSuspend(NULL); 
      }
		}
  }
  /* USER CODE END SemaphoreThread1 */
}

/* SemaphoreThread2 function */
void SemaphoreThread2(void const * argument)
{
  /* USER CODE BEGIN SemaphoreThread2 */
	uint32_t count = 0;
  /* Infinite loop */
  for(;;)
  {
        if (SEMHandle != NULL)
    {
      /* Try to obtain the semaphore. */
      if(osSemaphoreWait(SEMHandle , 0) == osOK)
      {
        /* Resume Thread 1 (higher priority)*/
        osThreadResume(SEM_Thread1Handle);
        
        count = osKernelSysTick() + 5000;
        
        /* Toggle LED2 every 200 ms for 5 seconds*/
        while (count >= osKernelSysTick())
        {
          BSP_LED_Toggle(LED2);
          
          osDelay(200);
        }
        
        /* Turn off LED2 */
        BSP_LED_Off(LED2);
        
        /* Release the semaphore to unblock Thread 1 (higher priority)  */
        osSemaphoreRelease(SEMHandle);
      }
    }
  }
  /* USER CODE END SemaphoreThread2 */
}

/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
