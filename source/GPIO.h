/*
 * GPIO.h
 * Declaracion de funciones, estructuras y direcciones para manipular y confugurar
 * los puertos de la k64.
 *
 *  Created on: 26 ene. 2024
 *   Author: Daniel Alfaro y Frida Hernandez.
 */

#ifndef GPIO_H_
#define GPIO_H_

#define PIN0_IDX        0u   /*!< Pin number for pin 0 in a port */
#define PIN1_IDX        1u   /*!< Pin number for pin 1 in a port */
#define PIN2_IDX        2u   /*!< Pin number for pin 2 in a port */
#define PIN3_IDX        3u   /*!< Pin number for pin 3 in a port */
#define PIN16_IDX       16u   /*!< Pin number for pin 16 in a port */
#define PIN17_IDX       17u   /*!< Pin number for pin 17 in a port */

#define PORT_DATA_OR_CMD_PIN PORTC
#define GPIO_DATA_OR_CMD_PIN GPIOC
#define DATA_OR_CMD_PIN 	5U
#define RESET_PIN 			7U
#define PORT_RESET_PIN 		PORTC
#define GPIO_RESET_PIN 		GPIOC

void GPIO_init(void);

#endif /* GPIO_H_ */
