/*
 * memory.c
 * Definicion de funciones que permiten la lectura de la memoria y mostrar las
 * imagenes en un orden especifico cada cierto tiempo.
 *
 *  Created on: 12 abr. 2024
 *  Author: Daniel Alfaro y Frida Hernandez.
 */
#include <stdint.h>
#include "memory.h"
#include "LCD_nokia.h"
#include "LCD_nokia_images.h"
#include "Delay.h"
#include "SPI.h"

//Direcciones de sectores donde se encuentran las imagenes guardadas en la memoria
const uint32_t Imagen_1 = 0x40000u;
const uint32_t Imagen_2 = 0x41000u;
const uint32_t Imagen_3 = 0x42000u;
const uint32_t Imagen_4 = 0x43000u;
const uint32_t Imagen_5 = 0x44000u;

static uint8_t counter = 0;

//Funcion selectora de imagenes segun el estado del contador
void print_pictures(void)
{
	uint8_t buffer[504] = {0};	//Arreglo donde se guardan los datos de la imagen a mostrar
	switch(counter%6)
	{
		case 1:
			LCD_nokia_clear();
			SPI_read_memory(Imagen_1, buffer);
			LCD_nokia_bitmap(buffer);
			break;
		case 2:
			LCD_nokia_clear();
			SPI_read_memory(Imagen_2, buffer);
			LCD_nokia_bitmap(buffer);
			break;

		case 3:
			LCD_nokia_clear();
			SPI_read_memory(Imagen_3, buffer);
			LCD_nokia_bitmap(buffer);
			break;

		case 4:
			LCD_nokia_clear();
			SPI_read_memory(Imagen_4, buffer);
			LCD_nokia_bitmap(buffer);
			break;
		case 5:
			LCD_nokia_clear();
			SPI_read_memory(Imagen_5, buffer);
			LCD_nokia_bitmap(buffer);
			break;
		default:
		LCD_nokia_clear();
		LCD_nokia_bitmap(get_ITESO());
		break;
	}
}

//Funcion que imprime las imagenes en la pantalla cada cierto delay
void Reproduce_picture(void)
{
	counter++;
	print_pictures();
	delay(60000);
}
