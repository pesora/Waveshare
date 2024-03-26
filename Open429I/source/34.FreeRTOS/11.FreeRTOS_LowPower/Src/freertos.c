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
osThreadId RxThreadHandle;
osThreadId TxThreadHandle;
osMessageQId osqueueHandle;

/* USER CODE BEGIN Variables */
/* The rate at which the Tx task sends to the queue. */
#define TX_DELAY                 (500)

/* The value that is sent from the Tx task to the Rx task on the queue. */
#define QUEUED_VALUE             (100)

/* The length of time the LED will remain on for.  It is on just long enough
   to be able to see with the human eye so as not to distort the power readings too
   much. */
#define LED_TOGGLE_DELAY         (20)
/* USER CODE END Variables */

/* Function prototypes -------------------------------------------------------*/
void QueueReceiveThread(void const * argument);
void QueueSendThread(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* USER CODE BEGIN FunctionPrototypes */
void PreSleepProcessing(uint32_t *ulExpectedIdleTime);
void PostSleepProcessing(uint32_t *ulExpectedIdleTime);


void PreSleepProcessing(uint32_t *ulExpectedIdleTime)
{
	  /* Called by the kernel before it places the MCU into a sleep mode because
  configPRE_SLEEP_PROCESSING() is #defined to PreSleepProcessing().

  NOTE:  Additional actions can be taken here to get the power consumption
  even lower.  For example, peripherals can be turned off here, and then back
  on again in the post sleep processing function.  For maximum power saving
  ensure all unused pins are in their lowest power state. */

	/* Disable the peripheral clock during Low Power (Sleep) mode.*/
//  __HAL_RCC_GPIOB_CLK_SLEEP_DISABLE();
  /* 
    (*ulExpectedIdleTime) is set to 0 to indicate that PreSleepProcessing contains
    its own wait for interrupt or wait for event instruction and so the kernel vPortSuppressTicksAndSleep 
    function does not need to execute the wfi instruction  
  */
  *ulExpectedIdleTime = 0;
  
  /*Enter to sleep Mode using the HAL function HAL_PWR_EnterSLEEPMode with WFI instruction*/
  HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);  
}

void PostSleepProcessing(uint32_t *ulExpectedIdleTime)
{
	/* Called by the kernel when the MCU exits a sleep mode because
  configPOST_SLEEP_PROCESSING is #defined to PostSleepProcessing(). */

  /* Avoid compiler warnings about the unused parameter. */
  (void) ulExpectedIdleTime;
}
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
  /* definition and creation of RxThread */
  osThreadDef(RxThread, QueueReceiveThread, osPriorityNormal, 0, 128);
  RxThreadHandle = osThreadCreate(osThread(RxThread), NULL);

  /* definition and creation of TxThread */
  osThreadDef(TxThread, QueueSendThread, osPriorityIdle, 0, 128);
  TxThreadHandle = osThreadCreate(osThread(TxThread), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* Create the queue(s) */
  /* definition and creation of osqueue */
  osMessageQDef(osqueue, 1, uint16_t);
  osqueueHandle = osMessageCreate(osMessageQ(osqueue), NULL);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
}

/* QueueReceiveThread function */
void QueueReceiveThread(void const * argument)
{

  /* USER CODE BEGIN QueueReceiveThread */
	osEvent event;
  /* Infinite loop */
  for(;;)
  {
    /* Wait until something arrives in the queue. */
    event = osMessageGet(osqueueHandle, osWaitForever);
    
    /*  To get here something must have arrived, but is it the expected
        value?  If it is, turn the LED on for a short while. */
    if(event.status == osEventMessage)
    {
      if(event.value.v == QUEUED_VALUE)
      {  
        BSP_LED_On(LED1);
        osDelay(LED_TOGGLE_DELAY);
        BSP_LED_Off(LED1);
      }			
    }		
  }
  /* USER CODE END QueueReceiveThread */
}

/* QueueSendThread function */
void QueueSendThread(void const * argument)
{
  /* USER CODE BEGIN QueueSendThread */
  /* Infinite loop */
  for(;;)
  {
    /* Place this thread into the blocked state until it is time to run again.
       The kernel will place the MCU into the Retention low power sleep state
       when the idle thread next runs. */
    osDelay(TX_DELAY);

    /* Send to the queue - causing the queue receive thread to flash its LED.
       It should not be necessary to block on the queue send because the Rx
       thread will already have removed the last queued item. */    
    osMessagePut(osqueueHandle, (uint32_t)QUEUED_VALUE, 0);
		BSP_LED_Toggle(LED2);
  }
  /* USER CODE END QueueSendThread */
}

/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
