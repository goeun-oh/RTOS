/*
 * Model_Distance.c
 *
 *  Created on: Jul 4, 2025
 *      Author: kccistc
 */


#include "Model_Distance.h"

static eDistanceState_t distanceState = S_IDLE;

osMessageQId distanceEventMsgBox;
osMessageQDef(distanceEventQueue, 16, uint16_t);

osMailQId distanceDataMailBox;
osMailQDef(distanceDataMailQueue, 4, distance_t);

void Model_DistanceInit(){
	distanceEventMsgBox = osMessageCreate(osMessageQ(distanceEventQueue), NULL);
	distanceDataMailBox = osMailCreate(osMailQ(distanceDataMailQueue), NULL);
}


void Model_SetDistanceState (eDistanceState_t state){
	distanceState = state;
}

eDistanceState_t Model_GetDistanceState(){
	return distanceState;
}
