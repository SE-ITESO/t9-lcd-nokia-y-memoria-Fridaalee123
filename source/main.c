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
	GPIO_init(); 				//Inicializacion de puertos y pines
	SPI_config_nokia_memory();	//Configuracion de la memoria
	LCD_nokia_init();			//Inicializacion de la pantalla LCD

	for(;;)
	{
		Reproduce_picture();	//Reproduce las imagenes en la pantalla periodicamente
	}
	return 0;
}

