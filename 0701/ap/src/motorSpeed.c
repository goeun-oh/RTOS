#include "motorSpeed.h"

static int motor_state = 0;
static uint32_t motor_prev_tick = 0;

void MotorSpeed_Init()
{
   Motor_Init(&htim1, TIM_CHANNEL_1);
   Motor_SetFreq(10000);  // 고정 주파수 //10khz
   Motor_Start();
}

void MotorSpeed_RunStateMachine()
{
   uint32_t now = HAL_GetTick();

   switch (motor_state)
   {
   case 0:
      Motor_SetPower(100);
      motor_prev_tick = now;
      motor_state++;
      break;
   case 1:
      if (now - motor_prev_tick >= 5000) {
         Motor_SetPower(80);
         motor_prev_tick = now;
         motor_state++;
      }
      break;
   case 2:
      if (now - motor_prev_tick >= 5000) {
         Motor_SetPower(70);
         motor_prev_tick = now;
         motor_state++;
      }
      break;
   case 3:
      if (now - motor_prev_tick >= 500) {
         Motor_SetPower(60);
         motor_prev_tick = now;
         motor_state++;
      }
      break;
   case 4:
      if (now - motor_prev_tick >= 500) {
         Motor_SetPower(50);
         motor_prev_tick = now;
         motor_state++;
      }
      break;
   case 5:
      if (now - motor_prev_tick >= 500) {
         Motor_Stop();
         motor_state++;
      }
      break;
   }
}
