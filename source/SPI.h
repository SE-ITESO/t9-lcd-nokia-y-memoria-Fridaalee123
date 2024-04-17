/*
 * SPI.h
 *
 *  Created on: 19 jun. 2021
 *      Author: jlpe
 */

#ifndef SPI_H_
#define SPI_H_

#include <stdint.h>

//Baudrate
#define TRANSFER_SIZE     64U     			/*! Transfer dataSize */
#define TRANSFER_BAUDRATE_NOKIA	 1000000U 	/*! Transfer baudrate - 500k */
#define TRANSFER_BAUDRATE_MEMORY 2000000U

//SPI memory
#define Read_data 		0x03
#define SIZE_TX_DATA 	4U
#define SIZE_RX_DATA 	1U

#define HIGH_PART 	0xF0000
#define MEDIUM_PART	0x0FF00
#define LOW_PART	0x000FF

void SPI_config_nokia_memory(void);
void SPI_read_memory(uint32_t direction,uint8_t buffer[]);

#endif /* SPI_H_ */
