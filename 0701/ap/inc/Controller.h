/*
 * Controller.h
 *
 *  Created on: Jun 24, 2025
 *      Author: rhoblack
 */

#ifndef AP_CONTROLLER_H_
#define AP_CONTROLLER_H_

#include "stopWatch.h"
#include "timeWatch.h"
#include "Model_Watch.h"


enum {MODE, STOPWATCH_RUN_STOP, STOPWATCH_CLEAR};
enum {MODE_NO_ACT, MODE_ACT, STOPWATCH_NO_ACT, STOPWATCH_ACT};

typedef struct {
	int id;
	int data;
}inputData_TypeDef;

void Controller_SetInputData(inputData_TypeDef inputData);
void Controller_Excute();

#endif /* AP_CONTROLLER_H_ */
