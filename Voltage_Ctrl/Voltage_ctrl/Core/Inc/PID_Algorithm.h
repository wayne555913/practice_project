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
#ifndef PID_Algorithm_H
#define PID_Algorithm_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stm32f1xx_ll_adc.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_tim.h"
#include "stm32f1xx.h"
#include "ADC_config.h"
#include "USART_OPERATION.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
typedef uint32_t (*ADC_Operation)();
typedef void (*Set_Duty)(float duty);




typedef struct {
    float Kp; // 比例增益
    float Ki; // 积分增益
    float Kd; // 微分增益
    float integral; // 积分项累计
    float derivative; // 微分项累计
    float error; // 误差项累计
    float prev_error; // 上一次的误差
    float current;
    float output_duty;


    ADC_Operation ADC_operation;
    Set_Duty Set_duty;


}PID_Controller;



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
void PID_Process(Config_Value target,PID_Controller *Temp,ADC_Operation func1,Set_Duty func2);

/*
*@param TIMX is filled with address ,such as TIM7
*@param ms 1 < ms < xxxx
*@make sure that input clk is 72MHZ
*/
void PID_Parameters_Init(PID_Controller *init_para,float Kp,float Ki,float Kd,ADC_Operation ADC_Opera,Set_Duty set_duty);









/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* _ADC_CONFIG_H */