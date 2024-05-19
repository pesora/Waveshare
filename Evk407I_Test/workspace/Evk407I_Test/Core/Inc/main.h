/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SEG1_C_Pin GPIO_PIN_2
#define SEG1_C_GPIO_Port GPIOE
#define SEG1_D_Pin GPIO_PIN_3
#define SEG1_D_GPIO_Port GPIOE
#define SEG2_A_Pin GPIO_PIN_4
#define SEG2_A_GPIO_Port GPIOE
#define SEG2_B_Pin GPIO_PIN_5
#define SEG2_B_GPIO_Port GPIOE
#define SEG2_C_Pin GPIO_PIN_6
#define SEG2_C_GPIO_Port GPIOE
#define LED_TEMP_G_Pin GPIO_PIN_0
#define LED_TEMP_G_GPIO_Port GPIOF
#define LED_TEMP_R_Pin GPIO_PIN_1
#define LED_TEMP_R_GPIO_Port GPIOF
#define LED_FAN1_G_Pin GPIO_PIN_2
#define LED_FAN1_G_GPIO_Port GPIOF
#define LED_FAN1_R_Pin GPIO_PIN_3
#define LED_FAN1_R_GPIO_Port GPIOF
#define LED_FAN2_G_Pin GPIO_PIN_4
#define LED_FAN2_G_GPIO_Port GPIOF
#define LED_FAN2_R_Pin GPIO_PIN_5
#define LED_FAN2_R_GPIO_Port GPIOF
#define LED_PDU_G_Pin GPIO_PIN_6
#define LED_PDU_G_GPIO_Port GPIOF
#define LED_PDU_R_Pin GPIO_PIN_7
#define LED_PDU_R_GPIO_Port GPIOF
#define LED_DP1_G_Pin GPIO_PIN_8
#define LED_DP1_G_GPIO_Port GPIOF
#define LED_DP2_G_Pin GPIO_PIN_9
#define LED_DP2_G_GPIO_Port GPIOF
#define LED_DP3_G_Pin GPIO_PIN_10
#define LED_DP3_G_GPIO_Port GPIOF
#define KEY_TEST_Pin GPIO_PIN_2
#define KEY_TEST_GPIO_Port GPIOC
#define KEY_TEST_EXTI_IRQn EXTI2_IRQn
#define LED_RUN_Pin GPIO_PIN_2
#define LED_RUN_GPIO_Port GPIOH
#define TIM2_CH1_IC1_Pin GPIO_PIN_5
#define TIM2_CH1_IC1_GPIO_Port GPIOA
#define TIM3_CH1_PWM4_Pin GPIO_PIN_6
#define TIM3_CH1_PWM4_GPIO_Port GPIOA
#define TIM3_CH3_PWM6_Pin GPIO_PIN_0
#define TIM3_CH3_PWM6_GPIO_Port GPIOB
#define LED_CHG_G_Pin GPIO_PIN_11
#define LED_CHG_G_GPIO_Port GPIOF
#define LED_CHG_R_Pin GPIO_PIN_12
#define LED_CHG_R_GPIO_Port GPIOF
#define LED_TEMP_GG0_Pin GPIO_PIN_0
#define LED_TEMP_GG0_GPIO_Port GPIOG
#define SEG2_D_Pin GPIO_PIN_7
#define SEG2_D_GPIO_Port GPIOE
#define TIM1_CH1_PWM1_Pin GPIO_PIN_9
#define TIM1_CH1_PWM1_GPIO_Port GPIOE
#define TIM1_CH2_PWM2_Pin GPIO_PIN_11
#define TIM1_CH2_PWM2_GPIO_Port GPIOE
#define TIM1_TCH3_PWM3_Pin GPIO_PIN_13
#define TIM1_TCH3_PWM3_GPIO_Port GPIOE
#define TIM2_CH3_IC3_Pin GPIO_PIN_10
#define TIM2_CH3_IC3_GPIO_Port GPIOB
#define TIM4_CH1_IC4_Pin GPIO_PIN_12
#define TIM4_CH1_IC4_GPIO_Port GPIOD
#define TIM4_CH2_IC5_Pin GPIO_PIN_13
#define TIM4_CH2_IC5_GPIO_Port GPIOD
#define TIM4_CH3_IC6_Pin GPIO_PIN_14
#define TIM4_CH3_IC6_GPIO_Port GPIOD
#define TIM3_CH2_PWM5_Pin GPIO_PIN_7
#define TIM3_CH2_PWM5_GPIO_Port GPIOC
#define INPUT_PG1_Pin GPIO_PIN_0
#define INPUT_PG1_GPIO_Port GPIOD
#define INPUT_PG2_Pin GPIO_PIN_1
#define INPUT_PG2_GPIO_Port GPIOD
#define INPUT_DP1_Pin GPIO_PIN_2
#define INPUT_DP1_GPIO_Port GPIOD
#define INPUT_DP3_Pin GPIO_PIN_4
#define INPUT_DP3_GPIO_Port GPIOD
#define INPUT_CHG_Pin GPIO_PIN_5
#define INPUT_CHG_GPIO_Port GPIOD
#define TIM2_CH2_IC2_Pin GPIO_PIN_3
#define TIM2_CH2_IC2_GPIO_Port GPIOB
#define I2C1_nRESET_Pin GPIO_PIN_8
#define I2C1_nRESET_GPIO_Port GPIOB
#define SEG1_A_Pin GPIO_PIN_0
#define SEG1_A_GPIO_Port GPIOE
#define SEG1_B_Pin GPIO_PIN_1
#define SEG1_B_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */