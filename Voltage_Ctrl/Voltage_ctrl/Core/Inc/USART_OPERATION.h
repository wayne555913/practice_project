/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : USART_OPERATION.h
  * @brief          : Header for USART_OPERATION.c file.
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
#ifndef __USART_OPERATION_H
#define __USART_OPERATION_H

#ifdef __cplusplus
extern "C" {
#endif

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
//#include "stdio.h"
#include "stm32f1xx_hal.h"
#include "delay_class.h"
#include "stm32f1xx.h"
//#include "PID_Algorithm.h"
#include "string.h"
/* USER CODE END Includes */
/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
#define data_length 7
#define ID 0x01

typedef enum {true =0,false =1,ack =2}Truth_Value;

typedef struct config_value
{
  /* data */
  float target;
  uint32_t interval; 
  uint32_t ADC_ZERO_INIT;

}Config_Value;




void Data_Inspect_By_StateMachine(TIM_HandleTypeDef *htim,uint8_t *buffer,uint8_t *Output_Data,uint8_t *exceed_time_flag);


__STATIC_INLINE Truth_Value ID_Judgement(uint8_t *data_temp)
{
  //enum truth_value judgement_result;
  if(*data_temp == ID)
  {
    return true;
  }
  else if (*data_temp == 0XFF)
  {
    return ack;
  }
  else
  return false;
}



void Set_Current(uint8_t *data_temp,Config_Value *target);

void Set_Interval(uint8_t *data_temp,Config_Value *target);

void ACK_Reaction(UART_HandleTypeDef *uart,uint8_t *data_temp);

void Function_Judge_Action(UART_HandleTypeDef *uart,uint8_t *data_temp,Config_Value *target);

__STATIC_INLINE void clean_temp(uint8_t *data_temp,uint8_t num)
{
  memset(data_temp,0,num);
}

void receiption_success(UART_HandleTypeDef *uart,uint8_t id);

__STATIC_INLINE void instruction_handle(UART_HandleTypeDef *uart,uint8_t *data_temp,Config_Value *target)
{
  //enum truth_value judgement_result;
  if(ID_Judgement(data_temp) == true)
  {
               // HAL_UART_Transmit(uart,"ok",strlen("ok"),1000);//receiption_success(uart,data_temp);
    Function_Judge_Action(uart,data_temp,target);

  }
  else if(ID_Judgement(data_temp) == ack)
  {
    ACK_Reaction(uart,data_temp);

  }
  else
  {
    //judgement_result = false;
  }
  clean_temp(data_temp,sizeof(data_temp));
}


  void auto_report_handle(UART_HandleTypeDef *uart,Config_Value *target);






/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/


/* USER CODE BEGIN EFP */

// int s_printf(unsigned char str,...);

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */




#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */