/*
 * Presenter.h
 *
 *  Created on: Jun 24, 2025
 *      Author: rhoblack
 */

#ifndef AP_PRESENTER_H_
#define AP_PRESENTER_H_

#include "Model_Watch.h"
#include "FND.h"
#include "lcd.h"
#include "LedBar.h"
#include "DHT11.h"
#include "tim.h"

void Presenter_Init();
void Presenter_OutData(watch_t watchData);
void Presenter_Excute();
void DHT11_Presenter_Display();

#endif /* AP_PRESENTER_H_ */
