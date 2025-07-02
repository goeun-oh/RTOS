/*
 * lcd.c
 *
 *  Created on: Jun 25, 2025
 *      Author: rhoblack
 */

#include "lcd.h"

#define LCD_RS	0
#define LCD_RW	1
#define LCD_E	2
#define LCD_BL	3

#define LCD_4BIT_FUNC_SET	0x28
#define LCD_DISP_OFF		0x08
#define LCD_DISP_ON			0x0C
#define LCD_DISP_CLEAR		0x01
#define LCD_ENTRY_MODE_SET	0x06

#define LCD_DEV_ADDR		0x27

static void LCD_cmdMode();
static void LCD_charMode();
static void LCD_writeMode();
static void LCD_E_High();
static void LCD_E_Low();
static void LCD_sendNibbleData(uint8_t data);
static void LCD_sendData(uint8_t data);
static void LCD_writeCmdData(uint8_t data);



static uint8_t lcdData = 0;
static I2C_HandleTypeDef *hLcdI2C;

void LCD_Init(I2C_HandleTypeDef *hI2C)
{
	hLcdI2C = hI2C;
	HAL_Delay(50);
	LCD_cmdMode();
	LCD_writeMode();
	LCD_sendNibbleData(0x30);
	HAL_Delay(5);
	LCD_sendNibbleData(0x30);
	HAL_Delay(1);
	LCD_sendNibbleData(0x30);
	LCD_sendNibbleData(0x20);
	LCD_sendData(LCD_4BIT_FUNC_SET);
	LCD_sendData(LCD_DISP_OFF);
	LCD_sendData(LCD_DISP_CLEAR);
	LCD_sendData(LCD_ENTRY_MODE_SET);
	LCD_sendData(LCD_DISP_ON);
	LCD_backLightOn();
}

void LCD_sendI2C(uint8_t data)
{
	HAL_I2C_Master_Transmit(hLcdI2C, LCD_DEV_ADDR<<1, &data, 1, 1000);
}

void LCD_backLightOn()
{
	lcdData |= (1<<LCD_BL);
}

void LCD_backLightOff()
{
	lcdData &= ~(1<<LCD_BL);
}

void LCD_cmdMode()
{
	lcdData &= ~(1<<LCD_RS);
	LCD_sendI2C(lcdData);
}

void LCD_charMode()
{
	lcdData |= (1<<LCD_RS);
	LCD_sendI2C(lcdData);
}

void LCD_writeMode()
{
	lcdData &= ~(1<<LCD_RW);
	LCD_sendI2C(lcdData);
}

void LCD_E_High()
{
	lcdData |= (1<<LCD_E);
	LCD_sendI2C(lcdData);
}

void LCD_E_Low()
{
	lcdData &= ~(1<<LCD_E);
	LCD_sendI2C(lcdData);
}

void LCD_sendNibbleData(uint8_t data)
{
	LCD_E_High();
	lcdData = (data & 0xf0) | (lcdData & 0x0f);
	LCD_sendI2C(lcdData);
	LCD_E_Low();
}

void LCD_sendData(uint8_t data)
{
	// High 4bit
	LCD_sendNibbleData(data);

	data = data << 4;
	// Low 4bit
	LCD_sendNibbleData(data);
}

void LCD_writeCmdData(uint8_t data)
{
	LCD_writeMode();
	LCD_cmdMode();
	LCD_sendData(data);
}

void LCD_writeCharData(uint8_t data)
{
	LCD_writeMode();
	LCD_charMode();
	LCD_sendData(data);
}

void LCD_writeString(char *str)
{
	for (int i=0; str[i]; i++) {
		LCD_writeCharData(str[i]);
	}
}

void LCD_gotoXY(uint8_t row, uint8_t col)
{
	col %= 16;
	row %= 2;

	uint8_t lcdRegAddr = (0x40 * row) +col;
	uint8_t command = 0x80 + lcdRegAddr;
	LCD_writeCmdData(command);
}

void LCD_writeStringXY(uint8_t row, uint8_t col, char *str)
{
	LCD_gotoXY(row, col);
	LCD_writeString(str);
}








