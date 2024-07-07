#include "PWM_Ctrl.h"

void Set_And_Convert_Duty(TIM_TypeDef *TIMX,int duty)
{
   float v;
   int temp1;
   int temp = LL_TIM_GetAutoReload (TIMX)+1;
   temp1 = duty*temp/100;
  // v = (duty/100.0) *temp- temp1; /////////////   Revert the cnt
   v = (duty/100.0) *temp;
   if (v > 0.5)
   {
      temp1 +=1;
   }
   

   //temp -= duty*temp/100;    /////////////   Revert the cnt

   temp = duty*temp/100;  

   LL_TIM_OC_SetCompareCH1(TIMX, temp);

   // LL_TIM_DisableAllOutputs (TIMX);

   // LL_TIM_DisableAutomaticOutput (TIMX);

   // LL_TIM_DisableCounter (TIMX);

}

void Set_And_Convert_Duty_Float(TIM_TypeDef *TIMX, float duty)
{
   float v;
   int temp1;
   int temp;
   if (duty > 0)
   {
      temp = LL_TIM_GetAutoReload (TIMX)+1;
      temp1 = (duty * temp)/100;
      v = (duty/100.0) *temp- temp1; ///////revert cnt

      if (v > 0.5)            
      {
         temp1 +=1;
      }
   }
   else
   {
      temp1 =0;
   }


   LL_TIM_OC_SetCompareCH1(TIMX, temp1);
/*
   LL_TIM_DisableAllOutputs (TIMX);

   LL_TIM_DisableAutomaticOutput (TIMX);

   LL_TIM_DisableCounter (TIMX);
   */
}
