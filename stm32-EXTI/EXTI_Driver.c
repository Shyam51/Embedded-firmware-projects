/*
 * EXTI_Driver.c
 *
 *  Created on: 11-Feb-2026
 *      Author: Shyam Maurya
 */


#include"EXTI_Driver.h"
#include <stdint.h>

 void EXTI_INit(GPIO_REG *pGPIOx,uint8_t PinNumber,uint8_t EdgeType){

	 /* 1. Enable SYSCFG clock */
	    RCC->APB2ENR |= (1 << 0);

	    /* 2. Configure SYSCFG EXTICR */
	        uint8_t portcode = 0;

	        if(pGPIOx == GPIOA) portcode = 0;
	        else if(pGPIOx == GPIOB) portcode = 1;
	        else if(pGPIOx == GPIOC) portcode = 2;
	        else if(pGPIOx == GPIOD) portcode = 3;
	        else if(pGPIOx == GPIOF) portcode = 5;

	        uint8_t exticr_index = (PinNumber / 4);
	        uint8_t exticr_pos   = ((PinNumber % 4) * 4);

	        SYSCFG->EXTICR[exticr_index] &= ~(0xF << exticr_pos);
	        SYSCFG->EXTICR[exticr_index] |=  (portcode << exticr_pos);

	        /* 3. Configure edge trigger */
	        if(EdgeType == EXTI_RISING_EDGE)
	        {
	            EXTI->RTSR |= (1 << PinNumber);
	            EXTI->FTSR &= ~(1 << PinNumber);
	        }
	        else if(EdgeType == EXTI_FALLING_EDGE)
	        {
	            EXTI->FTSR |= (1 << PinNumber);
	            EXTI->RTSR &= ~(1 << PinNumber);
	        }
	        else if(EdgeType == EXTI_RISING_FALLING)
	        {
	            EXTI->RTSR |= (1 << PinNumber);
	            EXTI->FTSR |= (1 << PinNumber);
	        }

	        /* 4. Unmask interrupt */
	        EXTI->IMR |= (1 << PinNumber);
	    }


 void EXTI_DeInit(uint8_t PinNumber)
 {
     EXTI->IMR  &= ~(1 << PinNumber);
     EXTI->RTSR &= ~(1 << PinNumber);
     EXTI->FTSR &= ~(1 << PinNumber);
 }


void EXTI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi)
	 {
	     if(EnorDi == ENABLE)
	     {
	         NVIC->ISER[0] |= (1 << IRQNumber);
	     }
	     else
	     {
	         NVIC->ICER[0] |= (1 << IRQNumber);
	     }
	 }
void EXTI_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority)
{
    uint8_t shift_amount = (8 - NO_PR_BITS_IMPLEMENTED);

    NVIC->IP[IRQNumber] &= ~(0xFF);  // clear previous
    NVIC->IP[IRQNumber] |= (IRQPriority << shift_amount);
}

