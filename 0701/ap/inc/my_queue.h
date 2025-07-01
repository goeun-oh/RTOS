/*
 * queue.h
 *
 *  Created on: Jun 25, 2025
 *      Author: rhoblack
 */

#ifndef AP_INC_MY_QUEUE_H_
#define AP_INC_MY_QUEUE_H_
#include "stm32f4xx_hal.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define QUE_SIZE	4

typedef struct {
	int front;
	int rear;
	int typeSize;
	void *queData[QUE_SIZE];
}Que_TypeDef;


void Que_Init(Que_TypeDef *q, int type_size);

void Que_DeInit(Que_TypeDef *q);

int isQueFull(Que_TypeDef *q);

int isQueEmpty(Que_TypeDef *q);

bool enQue(Que_TypeDef *q, void *pData);

bool deQue(Que_TypeDef *q, void *pData);

bool peekQue(Que_TypeDef *q, void *pData);




#endif /* AP_INC_MY_QUEUE_H_ */
