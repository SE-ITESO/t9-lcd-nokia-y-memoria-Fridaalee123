/*
 * GPIO.c
 * Se definen las funciones con las cuales se configuran y controlan los pines
 * de la tarjeta.
 *
 *  Created on: 26 ene. 2024
 *  Author: Daniel Alfaro y Frida Hernandez.
 */

#include "Bits.h"
#include "GPIO.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "fsl_clock.h"
#include "stdbool.h"


//Funciones de configuracion de puerto y pin
void GPIO_init(void)
{
	const port_pin_config_t port_D = {
				kPORT_PullUp,                 /* Internal pull-up resistor is enabled */
				kPORT_FastSlewRate,           /* Fast slew rate is configured */
				kPORT_PassiveFilterEnable,    /* Passive filter is disabled */
				kPORT_OpenDrainDisable,       /* Open drain is disabled */
				kPORT_HighDriveStrength,      /* High drive strength is configured */
				kPORT_MuxAlt2,                /* Pin is configured as PTA4 */
				kPORT_UnlockRegister          /* Pin Control Register fields [15:0] are not locked */
				};

	//Activar clock de cada puerto
	CLOCK_EnableClock(kCLOCK_PortA);
	CLOCK_EnableClock(kCLOCK_PortB);
	CLOCK_EnableClock(kCLOCK_PortC);
	CLOCK_EnableClock(kCLOCK_PortD);
	CLOCK_EnableClock(kCLOCK_PortE);

	//Configuracion de los pines
	PORT_SetPinConfig(PORTD, PIN0_IDX, &port_D);
	PORT_SetPinConfig(PORTD, PIN1_IDX, &port_D);
	PORT_SetPinConfig(PORTD, PIN2_IDX, &port_D);
	PORT_SetPinConfig(PORTD, PIN3_IDX, &port_D);
	PORT_SetPinMux(PORTC, PIN3_IDX, kPORT_MuxAlt2);	//Activa la ALT2 para SPI
}

