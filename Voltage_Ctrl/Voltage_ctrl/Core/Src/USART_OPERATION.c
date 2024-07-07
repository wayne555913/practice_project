#include "USART_OPERATION.h"
#include <stdarg.h>
#include <stdio.h>

// int s_printf(unsigned char str,...)
// {


//     // va_list args;


//     // va_start(args,str);
    
//     // int value = va_arg(args,int);

//     // //HAL_UART_Transmit(&huart1,usart_temp1,7,1000);

//     // va_end(args); 

//     // if(value == 97)
//     // {

//     // }
// }

void Data_Inspect_By_StateMachine(TIM_HandleTypeDef *htim,uint8_t *buffer,uint8_t *Output_Data,uint8_t *exceed_time_flag)
{
    static uint8_t state =0;
    static uint8_t cnt = 0;

    switch (state)
    {
    case 0:                      ///////////state 0
        /* code */
        if(*buffer != 0xaf)      //////////judge if reveive the start single
        {
            state =0;
        }
        else
        {
            state =1;
            // htim->Instance->SR =0;
            HAL_TIM_Base_Start_IT(htim);////open timer
            htim->Instance->CNT=0;
            *exceed_time_flag =0;
        }
        break;
    case 1:                       ///////////state 1
        if((cnt < data_length)&&(*exceed_time_flag == 0))
        {
            *(Output_Data+cnt) = *buffer;
            cnt++;
        }
        else if ((cnt >= data_length)&&(*exceed_time_flag == 0))
        {
            if(*buffer == 0XEF)
            {
                state =0;
                cnt =0;
                HAL_TIM_Base_Stop_IT(htim);  //////////close timer
                return;
            }
            else
            {
                for(uint8_t i =0;i < cnt;i++)
                {
                    *(Output_Data+i) = 0;
                }
                HAL_TIM_Base_Stop_IT(htim);//////////close timer
                state =0;
                cnt = 0;
                return;
            }
                *exceed_time_flag =0;
        }
        else if ((cnt < data_length)&&(*exceed_time_flag == 1))
        {
                for(uint8_t i =0;i < cnt;i++)
                {
                    *(Output_Data+i) = 0;
                }

                *exceed_time_flag =0;
                HAL_TIM_Base_Stop_IT(htim);//////////close timer
                state =0;
                cnt = 0;
                return;
        }

        break;
    }
}


void Set_Current(uint8_t *data_temp,Config_Value *target)
{
    uint32_t temp;
    for(int i=2;i<6;i++)
    {
        temp = temp<<8;
        temp = temp + *(data_temp+i);
    }

    target->target = temp;
    // if(target->target == 50528340)
    // HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_SET);

}


void Set_Interval(uint8_t *data_temp,Config_Value *target)
{
    uint32_t temp;
    for(int i=2;i<6;i++)
    {
        temp = temp<<8;
        temp = temp + *(data_temp+i);
    }

    target->interval = temp;
    // if(target->interval == 50528256)
    // HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_SET);
}

void ACK_Reaction(UART_HandleTypeDef *uart,uint8_t *data_temp)
{
    uint32_t temp;
    // temp = *(data_temp+2);
    // temp = temp<<8;
    // temp = temp + *(data_temp+3);
    // temp = temp<<8;
    // temp = temp + *(data_temp+4);
    // temp = temp<<8;
    // temp = temp + *(data_temp+5);
    for(int i=2;i<6;i++)
    {
        temp = temp<<8;
        temp = temp + *(data_temp+i);
    }

    if((*(data_temp+1) !=0x55)||(temp !=0xAAAAAAAA))      //////judge if report repeatedly
    HAL_UART_Transmit(uart,"Error!!!Can not receive correct data.",strlen("Error!!!Can not receive correct data."),1000);

}


void Function_Judge_Action(UART_HandleTypeDef *uart,uint8_t *data_temp,Config_Value *target)
{
    switch (*(data_temp+1))
    {
                    //HAL_UART_Transmit(uart,"ok",strlen("ok"),1000);//receiption_success(uart,data_temp);
       case 0X01:              ///////set the current
            Set_Current(data_temp,target);
            receiption_success(uart,0x01);
            break;
       case 0X02:              ///////set the interval
            Set_Interval(data_temp,target);

            receiption_success(uart,0x01);
            break;
    //   case 0X55:              ///////receive the ACK
    //     ACK_Reaction(data_temp);
            break;
      default:
            break;
    }

}


  void receiption_success(UART_HandleTypeDef *uart,uint8_t id)
  {

    uint8_t temp[]={0xaf,id,0xaa,0x55,0x55,0x55,0x55,0x00,0xef};

     HAL_UART_Transmit(uart,temp,9,1000);
     //us_delay(TIM7,100);

  }


    void auto_report_handle(UART_HandleTypeDef *uart,Config_Value *target)
    {
        static int cnt =0;

        ///report current data
        uint8_t temp[]={0xaf,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0xef};
        temp[3] = ((uint32_t)target->target)>>24;
        temp[4] = ((uint32_t)target->target)>>16;
        temp[5] = ((uint32_t)target->target)>>8;
        temp[6] = ((uint32_t)target->target);
        HAL_UART_Transmit(uart,temp,9,1000);
        //us_delay(TIM7,100);
         ///report interval data

        if(cnt >= 1000)
        {
            temp[3] = ((uint32_t)target->interval)>>24;
            temp[4] = ((uint32_t)target->interval)>>16;
            temp[5] = ((uint32_t)target->interval)>>8;
            temp[6] = ((uint32_t)target->interval);
            HAL_UART_Transmit(uart,temp,9,1000); 
            cnt =0; 
        }
        else
        {
            cnt++;
        }
    }