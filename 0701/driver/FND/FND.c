/*
 * FND.c
 *
 *  Created on: Jun 20, 2025
 *      Author: rhoblack
 */

#include "FND.h"

enum {DIGIT_1=0, DIGIT_10, DIGIT_100, DIGIT_1000, DIGIT_DP_1, DIGIT_DP_10, DIGIT_DP_100, DIGIT_DP_1000};

typedef struct {
	GPIO_TypeDef *GPIOx;
	uint32_t pinNum;
}FND_TypeDef;

FND_TypeDef fndDigitCom[4] = {
		{GPIOA, GPIO_PIN_12},
		{GPIOC, GPIO_PIN_5},
		{GPIOC, GPIO_PIN_6},
		{GPIOC, GPIO_PIN_8},
};

FND_TypeDef fndPin[8] = {
		{GPIOA, GPIO_PIN_11}, // A
		{GPIOB, GPIO_PIN_12}, // B
		{GPIOB, GPIO_PIN_2},  // C
		{GPIOB, GPIO_PIN_1},  // D
		{GPIOB, GPIO_PIN_15}, // E
		{GPIOB, GPIO_PIN_14}, // F
		{GPIOB, GPIO_PIN_13}, // G
		{GPIOC, GPIO_PIN_4},  // dp
};

//static void FND_DispOff(int fndPos);
void FND_DispOffAll();
static void FND_DispOn(int fndPos);
static void FND_DispDigit(uint16_t digit);

static uint16_t fndDispNum = 0; // fnd digit data
static uint8_t fndDispDp = 0;   // fnd dp data, xxxx1111 -> xxxx_dp1000_dp100_dp10_dp1



void FND_WriteDp(uint8_t dpData, uint8_t dpState)
{
	if (dpState == FND_DP_ON)
		fndDispDp |= dpData;
	else
		fndDispDp &= ~dpData;
}

// write fndDispNum
void FND_WriteData(uint16_t data)
{
	fndDispNum = data;
}

// read fndDispNum
uint16_t FND_ReadData()
{
	return fndDispNum;
}

// display fndDispNum
void FND_DispDataCallBack()
{
	static int digitPos = 0;
	// 인터럽트가 발생하면 한 자리씩 출력한다.
	digitPos = (digitPos+1) % 8;

	switch(digitPos)
	{
	case DIGIT_1:
		//FND_DispOff(digitPos);
		FND_DispOffAll();
		FND_DispDigit(fndDispNum%10);
		FND_DispOn(digitPos);
		break;
	case DIGIT_10:
		//FND_DispOff(digitPos);
		FND_DispOffAll();
		FND_DispDigit(fndDispNum/10%10);
		FND_DispOn(digitPos);
		break;
	case DIGIT_100:
		//FND_DispOff(digitPos);
		FND_DispOffAll();
		FND_DispDigit(fndDispNum/100%10);
		FND_DispOn(digitPos);
		break;
	case DIGIT_1000:
		//FND_DispOff(digitPos);
		FND_DispOffAll();
		FND_DispDigit(fndDispNum/1000%10);
		FND_DispOn(digitPos);
		break;
	case DIGIT_DP_1:
		//FND_DispOff(digitPos);
		FND_DispOffAll();
		if (fndDispDp & (1<<0)){
			FND_DispDigit(10); // DP ON
		}
		else {
			FND_DispDigit(11); // ALL OFF
		}
		FND_DispOn(digitPos%4);
		break;
	case DIGIT_DP_10:
		//FND_DispOff(digitPos);
		FND_DispOffAll();
		if (fndDispDp & (1<<1)){
			FND_DispDigit(10); // DP ON
		}
		else {
			FND_DispDigit(11); // ALL OFF
		}
		FND_DispOn(digitPos%4);
		break;
	case DIGIT_DP_100:
		//FND_DispOff(digitPos);
		FND_DispOffAll();
		if (fndDispDp & (1<<2)){
			FND_DispDigit(10); // DP ON
		}
		else {
			FND_DispDigit(11); // ALL OFF
		}
		FND_DispOn(digitPos%4);
		break;
	case DIGIT_DP_1000:
		//FND_DispOff(digitPos);
		FND_DispOffAll();
		if (fndDispDp & (1<<3)){
			FND_DispDigit(10); // DP ON
		}
		else {
			FND_DispDigit(11); // ALL OFF
		}
		FND_DispOn(digitPos%4);
		break;
	}
}

/*
void FND_DispOff(int fndPos)
{
	// GPIO_Write(GPIOx, Pin, SET);
	HAL_GPIO_WritePin(fndDigitCom[fndPos].GPIOx, fndDigitCom[fndPos].pinNum, SET);
}
*/

void FND_DispOn(int fndPos)
{
	// GPIO_Write(GPIOx, Pin, RESET);
	HAL_GPIO_WritePin(fndDigitCom[fndPos].GPIOx, fndDigitCom[fndPos].pinNum, RESET);
}

void FND_DispOffAll()
{
	for (int i=0; i<4; i++) {
		HAL_GPIO_WritePin(fndDigitCom[i].GPIOx, fndDigitCom[i].pinNum, SET);
	}
}

void FND_DispDigit(uint16_t digit)
{
	const uint8_t segFont[12] = {
	    0x3F,  // 0 => 00111111
	    0x06,  // 1 => 00000110
	    0x5B,  // 2 => 01011011
	    0x4F,  // 3 => 01001111
	    0x66,  // 4 => 01100110
	    0x6D,  // 5 => 01101101
	    0x7D,  // 6 => 01111101
	    0x07,  // 7 => 00000111
	    0x7F,  // 8 => 01111111
	    0x6F,  // 9 => 01101111
	    0x80,  // 10(dp) => 10000000
	    0x00,  // 11(off)=> 00000000
	};

	for (int i=0; i<8; i++) {
		if (!(segFont[digit] & (1<<i))) {
			HAL_GPIO_WritePin(fndPin[i].GPIOx, fndPin[i].pinNum, RESET);
		}
		else {
			HAL_GPIO_WritePin(fndPin[i].GPIOx, fndPin[i].pinNum, SET);
		}
	}
}





