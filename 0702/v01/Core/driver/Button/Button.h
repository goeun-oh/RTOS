/*
 * Button.h
 *
 *  Created on: Jun 19, 2025
 *      Author: rhoblack
 */

#ifndef DRIVER_BUTTON_BUTTON_H_
#define DRIVER_BUTTON_BUTTON_H_
#include "stm32f4xx_hal.h"

typedef enum {NO_ACT, ACT_PUSHED, ACT_RELEASED}button_state_t;

typedef struct {
	GPIO_TypeDef * GPIOx;
	uint16_t pinNum;
	uint32_t prevState;
}Button_Handler_t;

extern Button_Handler_t hBtnLed1;
extern Button_Handler_t hBtnLed2;
extern Button_Handler_t hBtnLed3;

void Button_Init(Button_Handler_t *hbtn, GPIO_TypeDef * GPIOx, uint16_t pinNum);
button_state_t Button_GetState(Button_Handler_t *hbtn);



#endif /* DRIVER_BUTTON_BUTTON_H_ */
