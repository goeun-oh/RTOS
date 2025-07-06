/*
 * Model_Mode.c
 *
 *  Created on: Jul 4, 2025
 *      Author: kccistc
 */

#include "Model_Mode.h"

static eModeState_t modeState= S_TIMEWATCH_MODE;

osMessageQId modeEventMsgBox;
osMessageQDef(modeEventQueue, 4, uint16_t);

void Model_ModeInit()
{
	modeEventMsgBox = osMessageCreate(osMessageQ(modeEventQueue), NULL);
}
// getter setter
void Model_SetModeState (eModeState_t state)
{
	modeState = state;
}

eModeState_t Model_GetModeState()
{
	return modeState;
}

