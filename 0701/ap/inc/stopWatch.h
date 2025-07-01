/*
 * stopWatch.h
 *
 *  Created on: Jun 23, 2025
 *      Author: rhoblack
 */

#ifndef AP_STOPWATCH_H_
#define AP_STOPWATCH_H_
#include "stm32f4xx_hal.h"
#include "Model_Watch.h"
#include "Controller.h"
#include "Presenter.h"

void StopWatch_IncTimeCallBack();
void StopWatch_IncTime();
void StopWatch_Excute();
void StopWatch_Stop();
void StopWatch_Run();
void StopWatch_Clear();


#endif /* AP_STOPWATCH_H_ */
