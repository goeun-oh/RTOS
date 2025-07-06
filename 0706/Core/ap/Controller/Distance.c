/*
 * Distance.c
 *
 *  Created on: Jul 4, 2025
 *      Author: kccistc
 */


#include "Distance.h"
#include <stdio.h>


distance_t distanceData;

static void Distance_Stop();
static void Distance_Start();
static void delay_us(uint16_t us);

void delay_us(uint16_t us)
{
	 uint32_t start = __HAL_TIM_GET_COUNTER(&htim4);
	 uint32_t target = start + us;

	    // 오버플로우 처리
	    if (target > 65535) {
	        target -= 65536;
	        while (__HAL_TIM_GET_COUNTER(&htim4) >= start); // 오버플로우 대기
	    }

	    while (__HAL_TIM_GET_COUNTER(&htim4) < target);
}

void Distance_Init(){
	distanceData.distance =0;
	distanceData.Trig_GPIOx = GPIOA;
	distanceData.Trig_pinNum = GPIO_PIN_7;
	distanceData.Echo_GPIOx = GPIOA;
	distanceData.Echo_pinNum = GPIO_PIN_6;

	distance_t *pdistanceData = osMailAlloc(distanceDataMailBox, 0);
	memcpy(pdistanceData, &distanceData, sizeof(distance_t));
	osMailPut(distanceDataMailBox, pdistanceData);
}

void Distance_Excute()
{
	eDistanceState_t state = Model_GetDistanceState();

	switch(state){
	case S_IDLE:
		Distance_Stop();
		break;
	case S_START:
		Distance_Start();
		break;
	default:
		break;
	}
}

void Distance_Stop()
{
	osEvent evt = osMessageGet(distanceEventMsgBox, 0);
	uint16_t evtState;

	if (evt.status == osEventMessage)
	{
		evtState = evt.value.v;

		if (evtState == EVENT_START){
			Model_SetDistanceState(S_START);
		}
	}

}
void Distance_Start()
{
	uint32_t start_time, end_time, duration;

	// 측정 간격 확보 (센서 안정화)
	static uint32_t last_measurement = 0;
	uint32_t current_time = HAL_GetTick();
	if (current_time - last_measurement < 60) { // 최소 60ms 간격
		return; // 너무 자주 측정 시도
	}
	last_measurement = current_time;

	// Trigger 펄스 발생
	HAL_GPIO_WritePin(distanceData.Trig_GPIOx, distanceData.Trig_pinNum, GPIO_PIN_SET);
	delay_us(10);
	HAL_GPIO_WritePin(distanceData.Trig_GPIOx, distanceData.Trig_pinNum, GPIO_PIN_RESET);

	// Echo 신호 High 대기
	uint32_t timeout_start = HAL_GetTick();
	while(!(HAL_GPIO_ReadPin(distanceData.Echo_GPIOx, distanceData.Echo_pinNum)))
	{
		if (HAL_GetTick() - timeout_start > 50) // 50ms 타임아웃
			return;
	}

	// Echo 시작 시간 기록
	start_time = __HAL_TIM_GET_COUNTER(&htim4);

	// Echo 신호 Low 대기
	timeout_start = HAL_GetTick();
	while(HAL_GPIO_ReadPin(distanceData.Echo_GPIOx, distanceData.Echo_pinNum))
	{
		if (HAL_GetTick() - timeout_start > 50) // 50ms 타임아웃
			return;
	}

	// Echo 종료 시간 기록
	end_time = __HAL_TIM_GET_COUNTER(&htim4);

	// 정확한 duration 계산 (오버플로우 고려)
	if (end_time >= start_time) {
		duration = end_time - start_time;
	} else {
		duration = (65536 - start_time) + end_time;
	}

	// 거리 계산 (타이머가 1MHz일 때만 유효)
	distanceData.distance = duration / 58;

	static distance_t prevDistanceData;
	// memory compare
	if(memcmp(&distanceData, &prevDistanceData, sizeof(distance_t))) {
		memcpy(&prevDistanceData, &distanceData, sizeof(distance_t));
		distance_t *pDistanceData = osMailAlloc(distanceDataMailBox, 0);
		memcpy(pDistanceData, &distanceData, sizeof(distance_t));
		osMailPut(distanceDataMailBox, pDistanceData);
	}
	// 유효성 검사 및 필터링
	if (distanceData.distance < 2 || distanceData.distance > 400) {
		return; // 범위 밖
	}

	// 극단적인 값 필터링 (하드웨어 노이즈 제거)
	if (distanceData.distance > 500) {
		return; // 명백한 오류값
	}
}
