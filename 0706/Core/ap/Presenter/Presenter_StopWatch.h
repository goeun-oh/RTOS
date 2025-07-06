/*
 * Presenter_StopWatch.h
 *
 *  Created on: Jul 3, 2025
 *      Author: kccistc
 */

#ifndef AP_PRESENTER_PRESENTER_STOPWATCH_H_
#define AP_PRESENTER_PRESENTER_STOPWATCH_H_
#include "cmsis_os.h"
#include "Model_StopWatch.h"
#include "FND.h"
#include "lcd.h"
#include "string.h"
#include "i2c.h"
#include "stdio.h"

void Presenter_StopWathInit();
void Presenter_StopWatchExcute();
void Presenter_StopWatch_FND(stopWatch_t StopWatchData);
void Presenter_StopWatch_LCD(stopWatch_t StopWatchData);
#endif /* AP_PRESENTER_PRESENTER_STOPWATCH_H_ */
