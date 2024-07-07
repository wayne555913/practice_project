/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : delay_class.h
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
#ifndef __DELAY_CLASS_H
#define __DELAY_CLASS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stm32f1xx_ll_tim.h"
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
__STATIC_INLINE void ms_delay(TIM_TypeDef *TIMX,int ms)
{
    int cnt;
//    TIMX.Instance = TIM7;
//    TIMX.Init.Prescaler = 0;
//    TIMX.Init.CounterMode = TIM_COUNTERMODE_UP;
//    TIMX.Init.Period = 65535;
//    htim7.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
     TIMX->CNT=0;
     LL_TIM_DisableCounter(TIMX);
     LL_TIM_ClearFlag_UPDATE(TIMX);
    //LL_TIM_SetUpdateSource(TIMX,LL_TIM_UPDATESOURCE_COUNTER);
   // LL_TIM_SetClockDivision (TIMX,267);
     LL_TIM_SetPrescaler(TIMX,267);
     LL_TIM_SetAutoReload(TIMX,267); 
     LL_TIM_EnableCounter(TIMX);
    for(cnt = 0;cnt < ms;cnt++)
    {

            while(LL_TIM_IsActiveFlag_UPDATE(TIMX)==0);
        
            LL_TIM_ClearFlag_UPDATE(TIMX); // 清除更新事件标志

            // 在这里执行计数事件触发后的操作
        
    }
    //LL_TIM_ClearFlag_UPDATE(TIMX);
    LL_TIM_DisableCounter(TIMX);
   // return __STATIC_INLINE void();
}

__STATIC_INLINE void us_delay(TIM_TypeDef *TIMX,int us)
{
    int cnt;
    // for(cnt = 0;cnt < us;cnt++)
    // {
     TIMX->CNT=0;
     LL_TIM_DisableCounter(TIMX);
     LL_TIM_ClearFlag_UPDATE(TIMX);

     LL_TIM_SetPrescaler(TIMX,6*us);
     LL_TIM_SetAutoReload(TIMX,120); 
     LL_TIM_EnableCounter(TIMX);


            while(LL_TIM_IsActiveFlag_UPDATE(TIMX)==0);
        
            LL_TIM_ClearFlag_UPDATE(TIMX); // 清除更新事件标志

            // 在这里执行计数事件触发后的操作
        
  //  }
    //LL_TIM_ClearFlag_UPDATE(TIMX);
    LL_TIM_DisableCounter(TIMX);
   // return __STATIC_INLINE void();
}




/*
*@param TIMX is filled with address ,such as TIM7
*@param ms 1 < ms < xxxx
*@make sure that input clk is 72MHZ
*/
__STATIC_INLINE void MX_TIM7_INIT(TIM_TypeDef *TIMX)
{

  /* USER CODE BEGIN TIM7_Init 0 */

  LL_TIM_InitTypeDef TIM_InitStruct = {0};

  /* USER CODE END TIM7_Init 0 */

  /* USER CODE BEGIN TIM7_Init 1 */
  switch ((int)TIMX)
  {
    case (int)TIM7:
    /* code */
     LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM7);//// Peripheral clock enable
    break;
  
    default:
    break;
  }

  /* USER CODE END TIM7_Init 1 */
  TIM_InitStruct.Prescaler = 0;
  TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
  TIM_InitStruct.Autoreload = 65535;
  LL_TIM_Init(TIMX, &TIM_InitStruct);
  LL_TIM_EnableARRPreload(TIMX);
  LL_TIM_SetTriggerOutput(TIMX, LL_TIM_TRGO_RESET);
  LL_TIM_DisableMasterSlaveMode(TIMX);
  /* USER CODE BEGIN TIM7_Init 2 */
  LL_TIM_GenerateEvent_UPDATE(TIMX);
  LL_TIM_DisableCounter(TIMX);
  /* USER CODE END TIM7_Init 2 */

}



/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __DELAY_CLASS_H */