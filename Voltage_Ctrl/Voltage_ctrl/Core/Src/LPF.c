#include "LPF.h"







uint32_t Sliding_Average_Fliter(int average_num,uint32_t ADC_Input)
{
    static unsigned char cnt =0;
    static uint32_t sum = 0;
    // static uint32_t average_value = 0;
    static uint32_t an[average_num];           ////////temp arry

    if(cnt < average_num)                      //////////1.culculate the sum of the first average_num items.
    {
        an[cnt] = ADC_Input;//////record the first average_num items into the an[];
        sum += ADC_Input;   //////accumulate the ADC_Inputs until reaching the average_num'th
        cnt++;
        return sum/cnt;     /////
    }
    else                                      /////2.if cnt beyond average_num,Sn = Sn-1 - a[n-m] + an,n>=average_num.
    {
        sum = sum - an[cnt-average_num]+ADC_Input;

        for(unsigned char i =0;i < (average_num-1);i++)    /////update the temp arry.
        {
            an[i] = an[i+1];
        }
        an[average_num-1] = ADC_Input;
        
        return sum/average_num;
    }

}