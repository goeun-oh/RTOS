/*
 * Presenter_Distance.c
 *
 *  Created on: Jul 4, 2025
 *      Author: kccistc
 */


#include "Presenter_Distance.h"

static void Presenter_Distance_FND(distance_t DistanceData);
static void Presenter_Distance_LCD(distance_t DistanceData);

void Presenter_DistanceInit(){

}

void Presenter_DistanceExcute(){
	static distance_t DistanceData;
	distance_t *pDistanceData;

	osEvent evt = osMailGet(distanceDataMailBox, 0);
	if (evt.status == osEventMail) {
		pDistanceData = evt.value.p;
		memcpy(&DistanceData, pDistanceData, sizeof(distance_t));
		osMailFree(distanceDataMailBox, pDistanceData);
		Presenter_Distance_FND(DistanceData);
		Presenter_Distance_LCD(DistanceData);
	}
}


void Presenter_Distance_FND(distance_t DistanceData)
{
	FND_WriteData(DistanceData.distance);
}

void Presenter_Distance_LCD(distance_t DistanceData)
{
	char str[30];
	sprintf(str, "%d      ", DistanceData.distance);
	LCD_writeStringXY(1, 0, str);
}
