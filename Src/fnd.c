#include "stm32f1xx.h"

void display_number(int pos, int value)
{
	int table[] = { 
		(0x1<<5) | (0x1<<4) | (0x1<<3) |(0x1<<2) | (0x1<<1) | (0x1<<0),
		(0x1<<2) | (0x1<<1),
		(0x1<<6) | (0x1<<4) | (0x1<<3) | (0x1<<1) | (0x1<<0),
		(0x1<<6) | (0x1<<3) | (0x1<<2) | (0x1<<1) | (0x1<<0),
		(0x1<<6) | (0x1<<5) | (0x1<<2) | (0x1<<1),
		(0x1<<6) | (0x1<<5) | (0x1<<3) | (0x1<<2) | (0x1<<0),
		(0x1<<6) | (0x1<<5) | (0x1<<4) | (0x1<<3) | (0x1<<2) | (0x1<<0),
		(0x1<<5) | (0x1<<2) | (0x1<<1) | (0x1<<0),
		(0x1<<6) | (0x1<<5) | (0x1<<4) | (0x1<<3) | (0x1<<2) | (0x1<<1) | (0x1<<0),
		(0x1<<6) | (0x1<<5) | (0x1<<3) | (0x1<<2) | (0x1<<1) | (0x1<<0),
	};

	//1
	GPIOC->ODR = GPIOC->ODR & ~ (0xFF << 0);

	//2
	GPIOB->ODR = GPIOB->ODR & ~ (0xF << 12);

  //3
  GPIOC->ODR = GPIOC->ODR | table[value];	
	
	//4
	GPIOB->ODR = GPIOB->ODR | (0x1 << (12 + pos)); 	
}

