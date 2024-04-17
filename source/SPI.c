/*
 * SPI.c
 *
 *  Created on: 12 mar. 2024
 *  Author: Frida Alejandra y Daniel Alfaro
 */

#include "Bits.h"
#include "SPI.h"
#include "fsl_dspi.h"
#include "fsl_port.h"
#include "fsl_gpio.h"
#include "fsl_clock.h"
#include "clock_config.h"

static const uint16_t SIZE = 504U;

void SPI_config_nokia_memory(void) //Configuracion del SPI
{
	dspi_master_config_t masterConfig;

	//Configuracion de la pnatalla Nokia
	masterConfig.whichCtar									 = kDSPI_Ctar0;								//Canal 0
	masterConfig.ctarConfig.baudRate 						 = TRANSFER_BAUDRATE_NOKIA;					//Velocidad de transmision
	masterConfig.ctarConfig.bitsPerFrame					 = 8U; 										//Bits que manejaran
	masterConfig.ctarConfig.cpol							 = kDSPI_ClockPolarityActiveHigh; 			//Polaridad 0
	masterConfig.ctarConfig.cpha   	    					 = kDSPI_ClockPhaseFirstEdge;     			//Phase 0
	masterConfig.ctarConfig.direction 						 = kDSPI_MsbFirst;							//Big endian?
	masterConfig.ctarConfig.pcsToSckDelayInNanoSec 			 = 1000000000U/ TRANSFER_BAUDRATE_NOKIA;	//Tiempo de espera para envio de datos y PCS on
	masterConfig.ctarConfig.lastSckToPcsDelayInNanoSec		 = 1000000000U/ TRANSFER_BAUDRATE_NOKIA;	//Tiempo de espera fin de envio de datos y PCS off
	masterConfig.ctarConfig.betweenTransferDelayInNanoSec	 = 1000000000U/ TRANSFER_BAUDRATE_NOKIA;	//Tiempo de espera entre un envio de datos y otro

	masterConfig.whichPcs           		= kDSPI_Pcs0;			//Seleccion de PCS 0
	masterConfig.pcsActiveHighOrLow 		= kDSPI_PcsActiveLow;
	masterConfig.enableContinuousSCK        = false;				//Detiene el SCK entre transfere
	masterConfig.enableRxFifoOverWrite      = false;				//Solo escribe cuando hay espacio disponible
	masterConfig.enableModifiedTimingFormat = false;				//Temporizacion estandar
	masterConfig.samplePoint                = kDSPI_SckToSin0Clock;	//Toma el dato en flanco ascendente

	uint32_t srcClock_hz = CLOCK_GetFreq(DSPI0_CLK_SRC);	//Configuracion de frecuencia de reloj
	DSPI_MasterInit(SPI0, &masterConfig, srcClock_hz);		//Inicializacion del bus

	//Configuracion de la Memoria
    masterConfig.whichCtar                                = kDSPI_Ctar1;					//Canal 1
    masterConfig.ctarConfig.baudRate                      = TRANSFER_BAUDRATE_MEMORY;		//Velocidad de transmision
    masterConfig.ctarConfig.bitsPerFrame                  = 8U;
    masterConfig.ctarConfig.cpol                          = kDSPI_ClockPolarityActiveHigh;
    masterConfig.ctarConfig.cpha                          = kDSPI_ClockPhaseFirstEdge;
    masterConfig.ctarConfig.direction                     = kDSPI_MsbFirst;
    masterConfig.ctarConfig.pcsToSckDelayInNanoSec        = 1000000000U / TRANSFER_BAUDRATE_MEMORY;
    masterConfig.ctarConfig.lastSckToPcsDelayInNanoSec    = 1000000000U / TRANSFER_BAUDRATE_MEMORY;
    masterConfig.ctarConfig.betweenTransferDelayInNanoSec = 1000000000U / TRANSFER_BAUDRATE_MEMORY;

    masterConfig.whichPcs           		= kDSPI_Pcs1;			//Seleccion de PCS 1
    masterConfig.pcsActiveHighOrLow			= kDSPI_PcsActiveLow;
    masterConfig.enableContinuousSCK        = false;
    masterConfig.enableRxFifoOverWrite      = false;
    masterConfig.enableModifiedTimingFormat = false;
    masterConfig.samplePoint                = kDSPI_SckToSin0Clock;

	DSPI_MasterInit(SPI0, &masterConfig, srcClock_hz);
	}


void SPI_read_memory(uint32_t direction, uint8_t buffer[])
{
    uint8_t data[4];	//Almacena los datos enviados a la memoria
    dspi_half_duplex_transfer_t master_memory;

    data[0] = Read_data;
    master_memory.txDataSize = SIZE_TX_DATA;	//Tamaño de los datos a transmitir
    master_memory.rxDataSize = SIZE_RX_DATA;	//Tamaño de los datos a enviar

    master_memory.isPcsAssertInTransfer = TRUE;	//Mantiene activo el PCS durante la transfer
    master_memory.isTransmitFirst = TRUE;		//Transmite antes de recibir

    master_memory.configFlags = kDSPI_MasterCtar1 | kDSPI_MasterPcs1 | kDSPI_MasterPcsContinuous;

    for(uint16_t counter = 0; counter < SIZE; counter++)
    {
        data[1] = ((direction) & HIGH_PART) >> bit_16;
        data[2] = ((direction+counter) & MEDIUM_PART)  >> bit_8;
        data[3] = ((direction+counter) & LOW_PART);
        master_memory.txData = data;			//Datos a enviar
        master_memory.rxData = buffer+counter;	//Donde se van a recibir los datos

        DSPI_MasterHalfDuplexTransferBlocking(SPI0, &master_memory); //Transferencia
    }
}
