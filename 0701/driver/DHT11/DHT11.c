/*
 * DHT11.c
 *
 *  Created on: Jun 26, 2025
 *      Author: kccistc
 */

#include "DHT11.h"
#include "stm32f4xx_hal.h"
#include "stdio.h"

#define DHT11_PORT GPIOC
#define DHT11_PIN GPIO_PIN_10

extern TIM_HandleTypeDef htim4;

static volatile uint32_t last_time = 0;
static volatile uint8_t bit_index = 0;
static volatile uint8_t data[5] = {0};
static volatile uint8_t dht11_rx_done = 0; // 수신 완료 플래그


void DHT11_DelayUs(uint32_t us)
{
   __HAL_TIM_SET_COUNTER(&htim4, 0);
   while(__HAL_TIM_GET_COUNTER(&htim4) < us);
}

// 18ms Low, 20~40us High
void DHT11_SendStartSignal()
{
   GPIO_InitTypeDef GPIO_InitStruct = {0};
   GPIO_InitStruct.Pin = DHT11_PIN;
   GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
   HAL_GPIO_Init(DHT11_PORT, &GPIO_InitStruct);

   HAL_GPIO_WritePin(DHT11_PORT, DHT11_PIN, RESET);   // Low 18ms 유지
   HAL_Delay(18);    // 18ms Low
   HAL_GPIO_WritePin(DHT11_PORT, DHT11_PIN, SET);
   // 바로 인터럽트 활성화
   __HAL_GPIO_EXTI_CLEAR_FLAG(DHT11_PIN);
   HAL_NVIC_ClearPendingIRQ(EXTI15_10_IRQn);
   HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
   DHT11_DelayUs(30);
   HAL_TIM_Base_Stop(&htim4);
   __HAL_TIM_SET_COUNTER(&htim4, 0);
   HAL_TIM_Base_Start(&htim4);
   // Input Mode + Exti 설정 외부 인터럽트 가능하게 설정
   GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
   GPIO_InitStruct.Pull = GPIO_NOPULL;
   HAL_GPIO_Init(DHT11_PORT, &GPIO_InitStruct);

   HAL_TIM_Base_Stop(&htim4);
   __HAL_TIM_SET_COUNTER(&htim4, 0);
   HAL_TIM_Base_Start(&htim4);

   // 수신 전에 초기화
   bit_index = 0;
   last_time =0;

   for (int i = 0; i < 5; i++) {
      data[i] = 0;
   }

   __HAL_GPIO_EXTI_CLEAR_FLAG(DHT11_PIN);
   HAL_NVIC_ClearPendingIRQ(EXTI15_10_IRQn);
   HAL_NVIC_EnableIRQ(EXTI15_10_IRQn); //GPIO 10번에서 15번까지 인터럽트 처리
}

void DHT11_ReadData(uint8_t *humidity, uint8_t *temperature)
{
    dht11_rx_done = 0;  // 수신 시작 전 초기화
    DHT11_SendStartSignal();

    // 수신 완료까지 기다림 (타임아웃을 걸어주는 게 안전)
    uint32_t startTick = HAL_GetTick();
    while (!dht11_rx_done)
    {
        if (HAL_GetTick() - startTick > 10) // 10ms 타임아웃
        {
            printf("Timeout: Data receive failed\n");
            return;
        }
    }

    uint8_t checksum = (data[0] + data[1] + data[2] + data[3]);

    if (data[4] == checksum)
    {
        *humidity = data[0];
        *temperature = data[2];
        return;
    }
    else
    {
        printf("Checksum Error\n");
    }
}


void DHT11_EXTI_Callback()
{
   uint32_t now = __HAL_TIM_GET_COUNTER(&htim4);
   uint32_t duration = now - last_time;
   last_time = now;

   if (HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN) == GPIO_PIN_SET)
   {
      // Rising edge
   }
   else
   {
      // Falling edge (bit 해석)
      if (bit_index == 0) {
         if (duration < 70 || duration > 90) {
            printf("DHT11 LOW : %lu\n", duration);
         }

      }
      else if (bit_index >= 1 && bit_index <= 40) {
         // bit_index 1~40 이 실제 40bit 데이터
         uint8_t byte_idx = (bit_index - 1) / 8;

         data[byte_idx] <<= 1;

         if (duration > 40)
            data[byte_idx] |= 1;

      }
      bit_index++;

      //40비트 수신 완료후 외부 인터럽트 비활성화
      if (bit_index > 40) {
         HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);
         dht11_rx_done =1;
      }
   }
}
