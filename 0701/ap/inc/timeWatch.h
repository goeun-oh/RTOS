/*
 * timeWatch.h
 *
 *  Created on: Jun 23, 2025
 *      Author: rhoblack
 */

#ifndef AP_TIMEWATCH_H_
#define AP_TIMEWATCH_H_
#include "stm32f4xx_hal.h"
#include "Model_Watch.h"
#include "Controller.h"
#include "Presenter.h"

void TimeWatch_IncTimeCallBack();
void TimeWatch_Excute();



#endif /* AP_TIMEWATCH_H_ */
