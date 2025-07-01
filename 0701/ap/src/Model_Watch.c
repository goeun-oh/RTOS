/*
 * Model_Watch.c
 *
 *  Created on: Jul 1, 2025
 *      Author: kccistc
 */


#include "Model_Watch.h"

Que_TypeDef btnQue;
Que_TypeDef stopWatchQue;


void Model_init(){
	Que_Init(&btnQue, sizeof(button_t));
	Que_Init(&stopWatchQue, sizeof(watch_t));
}


