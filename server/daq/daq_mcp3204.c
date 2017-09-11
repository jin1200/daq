/*
 * daq_mcp3204.c
 *
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#include "daq_mcp3204.h"
#include "../dmm/spi.h"
#include "../dmm/uart.h"

uint8_t DAQ_MCP3204_Send(uint8_t data) {
	uint8_t returnValue;
	// Set clock rate fck/16
	SPCR |= (1<<SPR0);

	returnValue = SPI_MasterTransferRead(data);

	// Reset clock rate for LCD and Dataflash
	SPCR &= ~(1<<SPR0);

	return returnValue;
}

void DAQ_MCP3204_Init() {
	SPI_MasterInit();

	// Set MCP3204 Chip Select as Output
	DDRA |= (1<<PA1);


	MCP3204_Chip_Unselect;
}

void DAQ_MCP3204_Read_Channel(uint8_t channel, uint16_t *value) {
	*value = 0;

	static unsigned char returnValue;

	// Backup Status Register and disable Interrupts
	uint8_t sreg = SREG;
	cli();

	MCP3204_Chip_Select;

	DAQ_MCP3204_Send(MCP3204_START_BYTE);
	returnValue = DAQ_MCP3204_Send(channel<<6); // Read First Channel

	*value = (returnValue & 0b00001111) << 8;

	returnValue = DAQ_MCP3204_Send(MCP3204_DONT_CARE_BYTE);


	*value += returnValue;

	MCP3204_Chip_Unselect;

	// Restore Status Register
	SREG = sreg;

}
