/*
 * GPIO_Driver.c
 *
 *  Created on: 05-Feb-2026
 *      Author: Shyam Maurya
 */
#include"GPIO_Driver.h"
#include <stdint.h>


void GPIO_ClockControl(GPIO_REG *pGPIOX, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(pGPIOX  == GPIOA)
		{
			GPIOA_CLK_EN();
		}
		else if (pGPIOX == GPIOB)
		{
			GPIOB_CLK_EN();
		}
		else if (pGPIOX == GPIOC)
		{
			GPIOC_CLK_EN();
		}
		else if (pGPIOX == GPIOD)
		{
			GPIOD_CLK_EN();
		}
		else if (pGPIOX == GPIOF)
		{
			GPIOF_CLK_EN();
		}
	}
		else if(EnorDi == DISABLE)
	 {
			if(pGPIOX  == GPIOA)
					{
						GPIOA_CLK_DI();
					}
					else if (pGPIOX == GPIOB)
					{
						GPIOB_CLK_DI();
					}
					else if (pGPIOX == GPIOC)
					{
						GPIOC_CLK_DI();
					}
					else if (pGPIOX == GPIOD)
					{
						GPIOD_CLK_DI();
					}
					else if (pGPIOX == GPIOF)
					{
						GPIOF_CLK_DI();
					}
		}
	}

void GPIO_init(GPIO_REG *pGPIOX,
		uint8_t PinNumber,
		uint8_t PinMode,
		uint8_t PinSpeed,
		uint8_t PinPuPdControl,
		uint8_t PinOType,
		uint8_t PinAltFunMode)
{
//mode of gpio
	uint32_t tempreg = 0;
	tempreg |= (PinMode << 2*PinNumber);
	pGPIOX->MODER &= ~(3<<2*PinNumber);
	pGPIOX->MODER |= tempreg;
	//SPEED MODE
    tempreg = 0;
	tempreg |= (PinSpeed << 2*PinNumber);
	pGPIOX->OSPEEDR &= ~(3<<2*PinNumber);
	pGPIOX->OSPEEDR |= tempreg;
	//PULL UP AND PULL DOWN
	tempreg = 0;
	tempreg |= (PinPuPdControl << 2*PinNumber);
	pGPIOX->PUPDR &= ~(3<<2*PinNumber);
	pGPIOX->PUPDR |= tempreg;
	//PIN OUTPUT TYPE
	tempreg = 0;
	tempreg |= (PinOType << PinNumber);
	pGPIOX->OTYPER &= ~(1<<PinNumber);
	pGPIOX->OTYPER |= tempreg;
	//ALTERNATE FUNTION MODE
	if(PinNumber < 7){
		tempreg = 0;
		tempreg |= (PinAltFunMode << 4*PinNumber);
		pGPIOX->AFRL &= (15 << 4*(PinNumber % 8));
		pGPIOX->AFRL |= tempreg;
	}
	else if(PinNumber > 7){
		tempreg = 0;
				tempreg |= (PinAltFunMode << 4*PinNumber);
				pGPIOX->AFRH &= ~(15 << (4*PinNumber));
				pGPIOX->AFRH |= tempreg;
	}
}

void GPIO_Deinti(GPIO_REG *pGPIOX)
{

	if(pGPIOX == GPIOA)
	{
		RCC->AHBRSTR |= (1<<17);
	}
	else if (pGPIOX == GPIOB)
	{
		RCC->AHBRSTR |= (1<<18);
	}
	else if (pGPIOX == GPIOC)
	{
		RCC->AHBRSTR |= (1<<19);
	}
	else if (pGPIOX == GPIOD)
	{
		RCC->AHBRSTR |= (1<<20);
	}
	else if (pGPIOX == GPIOF)
	{
		RCC->AHBRSTR |= (1<<22);
	}
}

uint8_t GPIO_READ_PIN(GPIO_REG *pGPIOX,uint8_t PinNumber){
	uint8_t value;
	value = (((pGPIOX->IDR)>>PinNumber) & 0x00000001);
	return value;
}

uint16_t GPIO_READ_PORT(GPIO_REG *pGPIOX)
{
uint16_t value;
value = (pGPIOX->IDR);
return value;
}

void GPIO_WRITE_PIN(GPIO_REG *pGPIOX,uint8_t PinNumber,uint8_t value)
{
	if(value == 1)
		{
			pGPIOX->ODR |= (1<<PinNumber);
		}
		else{
			pGPIOX->ODR &= ~(1<<PinNumber);
		}
}

void GPIO_WRITE_PORT(GPIO_REG *pGPIOX,uint16_t value){
	pGPIOX->ODR = value;
}
