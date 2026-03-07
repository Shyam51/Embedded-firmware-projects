/*
 * EXTI_Driver.h
 *
 *  Created on: 11-Feb-2026
 *      Author: Shyam Maurya
 */

#ifndef EXTI_DRIVER_H_
#define EXTI_DRIVER_H_



#endif /* EXTI_DRIVER_H_ */

#include"stm32f070x.h"

//Edge selection macros
#define EXTI_RISING_EDGE        1
#define EXTI_FALLING_EDGE       2
#define EXTI_RISING_FALLING     3

//FUNCTION PROTOTYPE
 void EXTI_INit(GPIO_REG *pGPIOx,uint8_t PinNumber,uint8_t EdgeType);
 void EXTI_DEInit(uint8_t PinNumber);
 void EXTI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
 void EXTI_IRQPriorityConfig(uint8_t IRQNumber,uint8_t IRQPriority);
