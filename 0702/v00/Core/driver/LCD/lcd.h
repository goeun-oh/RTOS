/*
 * lcd.h
 *
 *  Created on: Jun 25, 2025
 *      Author: rhoblack
 */

#ifndef DRIVER_LCD_LCD_H_
#define DRIVER_LCD_LCD_H_
#include "stm32f4xx_hal.h"
#include "i2c.h"

void LCD_Init(I2C_HandleTypeDef *hI2C);
void LCD_backLightOn();
void LCD_backLightOff();
void LCD_writeCharData(uint8_t data);
void LCD_writeString(char *str);
void LCD_gotoXY(uint8_t row, uint8_t col);
void LCD_writeStringXY(uint8_t row, uint8_t col, char *str);

#endif /* DRIVER_LCD_LCD_H_ */
