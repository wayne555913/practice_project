#include "PID_Algorithm.h"

// PID_Controller temp2;

void PID_Process(Config_Value target,PID_Controller *Temp,ADC_Operation func1, Set_Duty func2)
{
    uint32_t temp2;

    Temp->prev_error = Temp->error;             ////////record the current error

    Temp->error = target.target - Temp->current;         ////////calculate the error between target and Current value of current

    Temp->integral += Temp->error;                ////////accumulate the error

    Temp->derivative = Temp->error - Temp->prev_error;     ////////// calculate the derivative of the error

    Temp->output_duty = (Temp->Kp)*(Temp->error) + (Temp->Ki)*(Temp->integral) + (Temp->Kd)*(Temp->derivative );
    ///////////calculate the output value using PID

    func2(Temp->output_duty);        ///////transfer the output value to TIM

    temp2 = func1();

    Temp->current = (float)(target.ADC_ZERO_INIT - temp2);         ///////read current value of current
}

void PID_Parameters_Init(PID_Controller *init_para,float Kp,float Ki,float Kd,ADC_Operation ADC_Opera,Set_Duty set_duty)
{

    init_para->Kp = Kp;
    init_para->Ki = Ki;
    init_para->Kd = Kd;

    init_para->integral = 0;
    init_para->derivative = 0;
    init_para->prev_error =0;

    init_para->current = 0;
    init_para->output_duty = 0;
    init_para->ADC_operation = ADC_Opera;
    init_para->Set_duty = set_duty;


}
