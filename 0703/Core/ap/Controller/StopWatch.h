/*
 * StopWatch.h
 *
 *  Created on: Jul 3, 2025
 *      Author: kccistc
 */

#ifndef AP_CONTROLLER_STOPWATCH_H_
#define AP_CONTROLLER_STOPWATCH_H_

#include <Model_StopWatch.h>
#include "cmsis_os.h"
#include "string.h"
#include "stdint.h"

void StopWatch_Excute();
void StopWatch_Stop();
void StopWatch_Run();
void StopWatch_Clear();
void StopWatch_IncTimeCallBack();

#endif /* AP_CONTROLLER_STOPWATCH_H_ */
