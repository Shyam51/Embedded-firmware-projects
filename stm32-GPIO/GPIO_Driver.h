/*
 * GPIO_Driver.h
 *
 *  Created on: 05-Feb-2026
 *      Author: Shyam Maurya
 */

#ifndef GPIO_DRIVER_H_
#define GPIO_DRIVER_H_


#include"stm32f070x.h"


#endif /* GPIO_DRIVER_H_ */

void GPIO_ClockControl(GPIO_REG *pGPIOX, uint8_t EnorDi);

void GPIO_init(GPIO_REG *pGPIOX,
		uint8_t PinNumber,
		uint8_t PinMode,
		uint8_t PinSpeed,
		uint8_t PinPuPdControl,
		uint8_t PinOType,
		uint8_t PinAltFunMode);

void GPIO_Deinti(GPIO_REG *pGPIOX);

//input read
uint8_t GPIO_READ_PIN(GPIO_REG *pGPIOX,uint8_t PinNumber);

uint16_t GPIO_READ_PORT(GPIO_REG *pGPIOX);

void GPIO_WRITE_PIN(GPIO_REG *pGPIOX,uint8_t PinNumber,uint8_t value);
void GPIO_WRITE_PORT(GPIO_REG *pGPIOX,uint16_t value);
