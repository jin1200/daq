/*
 * daq_mcp3204.h
 *
 */

#ifndef DAQ_MCP3204_H_
#define DAQ_MCP3204_H_

#define MCP3204_Chip_Select		(PORTA &= ~(1<<PA1))
#define MCP3204_Chip_Unselect	(PORTA |= (1<<PA1))

#define MCP3204_START_BYTE		0b00000110
#define MCP3204_DONT_CARE_BYTE	0b00000000

uint8_t DAQ_MCP3204_Send(uint8_t data);
void DAQ_MCP3204_Init();
void DAQ_MCP3204_Read_Channel(uint8_t channel, uint16_t *value);

#endif /* DAQ_MCP3204_H_ */
