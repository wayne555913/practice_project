/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : ADC_config.h
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
#ifndef _ADC_CONFIG_H
#define _ADC_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stm32f1xx_ll_adc.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
//TIM_HandleTypeDef htim7;


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
*@param TIMX is filled with address ,such as TIM7
*@param ms 1 < ms < xxxx
*@make sure that input clk is 72MHZ
*/
__STATIC_INLINE uint32_t ADC_By_Consultant(ADC_TypeDef *ADCx)
{

    LL_ADC_REG_StartConversionSWStart (ADCx);
    while(LL_ADC_IsActiveFlag_EOS (ADCx)==0);


    LL_ADC_ClearFlag_EOS(ADCx);

    return (LL_ADC_REG_ReadConversionData12(ADCx));
}
/*
*@param TIMX is filled with address ,such as TIM7
*@param ms 1 < ms < xxxx
*@make sure that input clk is 72MHZ
*/

__STATIC_INLINE uint32_t ADC1_Operation()
{
  return ADC_By_Consultant(ADC1);
}
/*
*@param TIMX is filled with address ,such as TIM7
*@param ms 1 < ms < xxxx
*@make sure that input clk is 72MHZ
*/
__STATIC_INLINE uint32_t ADC1_Operation_CALIB(uint32_t Calibrated_Value)
{
  return (ADC_By_Consultant(ADC1)-Calibrated_Value);
}

/*
*get the initial value of ADC1
*
*
*/
__STATIC_INLINE void Get_ADC_INIT_VALUE(uint32_t *Output)
{
  Set_And_Convert_Duty(TIM1,0);   ////////////close the PWM

  *Output = ADC_By_Consultant(ADC1);
}









/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* _ADC_CONFIG_H */