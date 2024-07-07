/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : PWM_Ctrl.h
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
#ifndef __PWM_CTRL_H
#define __PWM_CTRL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/


/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "delay_class.h"
#include "stdio.h"
#include "USART_OPERATION.h"

#include "stm32f1xx_ll_tim.h"
#include "stm32f1xx.h"
#include "stm32f1xx_hal.h"
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


/* USER CODE BEGIN EFP */
/*
*   start Advance_TIMX_PWM
*
*/
__STATIC_INLINE void Advance_TIMX_PWM_INIGTION(TIM_TypeDef *TIMX)
{
      /* Enable counter */
  /* Enable TIM1 main output */
  LL_TIM_CC_EnableChannel(TIMX, LL_TIM_CHANNEL_CH1 | LL_TIM_CHANNEL_CH1N);
  LL_TIM_EnableCounter(TIMX);
  LL_TIM_EnableAllOutputs(TIMX);
  LL_TIM_EnableAutomaticOutput(TIMX);

}



//void Set_And_Convert_Duty_Int(TIM_TypeDef *TIMX,int duty);


void Set_And_Convert_Duty(TIM_TypeDef *TIMX,int duty);


void Set_And_Convert_Duty_Float(TIM_TypeDef *TIMX,float duty);

__STATIC_INLINE void Set_And_Convert_Duty_ALL(float duty)
{
  Set_And_Convert_Duty_Float(TIM1,duty);
}

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
