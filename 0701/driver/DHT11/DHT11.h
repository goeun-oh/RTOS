/*
 * DHT11.h
 *
 *  Created on: Jun 27, 2025
 *      Author: kccistc
 */

#ifndef DRIVER_DHT11_DHT11_H_
#define DRIVER_DHT11_DHT11_H_
#include "stm32f4xx_hal.h"

void DHT11_ReadData(uint8_t *humidity, uint8_t *temperature);
void DHT11_SendStartSignal();
void DHT11_DelayUs(uint32_t us);
void DHT11_EXTI_Callback();

#endif /* DRIVER_DHT11_DHT11_H_ */
