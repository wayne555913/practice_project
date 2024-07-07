#include "delay_class.h"



/*
*@param TIMX is filled with address ,such as TIM7
*@param ms 1 < ms < xxxx
*@make sure that input clk is 72MHZ
*/
// __STATIC_INLINE void ms_delay(TIM_TypeDef *TIMX, int ms)
// {
//     int cnt;
// //    TIMX.Instance = TIM7;
// //    TIMX.Init.Prescaler = 0;
// //    TIMX.Init.CounterMode = TIM_COUNTERMODE_UP;
// //    TIMX.Init.Period = 65535;
// //    htim7.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
//     LL_TIM_DisableCounter(TIMx);


//     LL_TIM_SetClockDivision (TIMx,267);
//     LL_TIM_SetCounter (TIMx,267);

//     for(cnt = 0;cnt < ms;cnt++)
//     {
//         LL_TIM_EnableCounter(TIMx);
//         while(LL_TIM_IsActiveFlag_Update(TIMx));
//         LL_TIM_ClearFlag_Update(TIMx);
//     }
//     //LL_TIM_ClearFlag_UPDATE(TIMx);
//     //LL_TIM_EnableCounter(TIMx);
//    // return __STATIC_INLINE void();
// }
////void ms_delay(TIM_TypeDef *TIMX,int ms)
