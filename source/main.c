/*
 * main.c
 *
 *  Created on: 12 mar. 2024
 *  Author: Frida Alejandra y Daniel Alfaro
 */

#include "stdint.h"
#include "SPI.h"
#include "GPIO.h"
#include "Bits.h"


int main(void)
{
	GPIO_init();
	SPI_config_nokia_memory();

	for(;;)
	{

	}
	return 0;
}

