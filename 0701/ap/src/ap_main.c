/*
 * ap_main.c
 *
 *  Created on: Jun 19, 2025
 *      Author: rhoblack
 */

#include "ap_main.h"



int ap_main()
{


	//HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	while(1)
	{
		MotorSpeed_RunStateMachine();
		Listener_Excute();
		Controller_Excute();
		Presenter_Excute();
	}

	return 0;
}

void ap_init()
{
	Listener_Init();
	Presenter_Init();
	Sound_Init();
	Sound_PowerOn();
	MotorSpeed_Init();
	htim4.Instance = TIM4;
	htim4.Init.Prescaler = 84 - 1;    // (84MHz / 84 = 1MHz → 1us per count)
	htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim4.Init.Period = 0xFFFF;       // 최대 주기
	htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	HAL_TIM_Base_Init(&htim4);

}



