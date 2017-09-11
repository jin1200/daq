/*
 * main.c
 *
 */

# define F_CPU 16000000UL
# define NUM_CHANNELS 4

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "dmm/lcd.h"
#include "dmm/uart.h"
#include "daq/daq_lcd.h"
#include "daq/daq_mcp3204.h"
#include "daq/daq_esp01.h"
#include "daq/daq_lut.h"

uint16_t channel_value[NUM_CHANNELS];
float channel_float[NUM_CHANNELS];
char channel_value_string[NUM_CHANNELS][17];
char channel_value_str[NUM_CHANNELS][9];

// EEPROM: 4KB
// Inhalt: 4 x LUT: 4 x 4096 x 16 Bit

typedef struct {
	char short_name[17];
	char unit[6];
	enum {
		LUT, LINEAR, INACTIVE
	} type;
	float m;
	float b;
	uint8_t lut_number;
} channel_konf;

channel_konf channel_konfig[NUM_CHANNELS];

void ioinit() {
	DDRB = (1 << PB1) | (1 << PB2);
}

void long_delay(uint16_t ms) {
	for (; ms > 0; ms--)
		_delay_ms(1);
}

void init_timer() {
	TCCR1B |= (1 << WGM12); // configure timer1 for ctc mode
	TIMSK1 |= (1 << OCIE1A); // enable the CTC interrupt
	OCR1A = 19531; // set the CTC compare value
	// TODO: Set the right value
}

void start_timer() {
	TCCR1B |= ((1 << CS10 | 1 << CS12));
}

void init_debug_konfig() {
	channel_konfig[0].type = LINEAR;
	//channel_konfig[0].m = 0.0244140625; // 100%/4096
	channel_konfig[0].m = 0.02442002443;
	channel_konfig[0].b = 0;
	strcpy(channel_konfig[0].unit, "%");
	strcpy(channel_konfig[0].short_name, "Potentiometer");

	channel_konfig[1].type = LUT;
	channel_konfig[1].lut_number = 1;
	strcpy(channel_konfig[1].unit, "lx");
	strcpy(channel_konfig[1].short_name, "Fotoresistor");

	channel_konfig[2].type = LUT;
	channel_konfig[2].lut_number = 0;
	strcpy(channel_konfig[2].unit, "C");
	strcpy(channel_konfig[2].short_name, "Temperatur");

	channel_konfig[3].type = INACTIVE;
}

char * trimwhitespace(char * src) {
	// Delete leading whitesace (' ') from src string
	uint8_t i = 0;

	while (src[i] == ' ')
		i++;

	return (src + i);
}

char * getLine(char * src, char * line_string) {
	uint8_t i;
	// read until line-feed (LF = \n)
	while (1) {
		line_string[i] = src[i];
		if (line_string[i] == '\n' && line_string[i - 1] == '\r')
			break;
		i++;
	}
	// terminate with null-byte and delete termination bytes (\r\n)
	line_string[i - 1] = 0;

	// if availiable: return pointer to new line
	if (src[i + 1] == 0) {
		// End of string
		return NULL;
	}
	return (src + i + 1);
}

char * getNextCSVValue(char * csv_src, char * csv_value_string) {
	uint8_t i;

	while (1) {
		csv_value_string[i] = csv_src[i];
		if (csv_value_string[i] == ';' || csv_value_string[i] == 0) {
			break;
		}
		i++;
	}
	csv_value_string[i - 1] = 0;

	// if availiable: return pointer to new line
	if (csv_src[i + 1] == 0) {
		// End of string
		return NULL;
	}
	return (csv_src + i + 1);
}

void handleDATARequest(uint8_t linkID, char * response_data) {
	char one_channel_response[41];
	for (uint8_t id = 0; id < NUM_CHANNELS; id++) {
		if (channel_konfig[id].type != INACTIVE) {
			sprintf(one_channel_response, "%d;\"%s\";\"%s\"\r\n", id,
					channel_konfig[id].short_name,
					trimwhitespace(channel_value_string[id]));
		} else {
			sprintf(one_channel_response, "%d;null;null\r\n", id);
		}
		strcat(response_data, one_channel_response);
	}
	DAQ_ESP01_Send_Data(linkID, response_data);
}

void handleLUTRequest(uint8_t linkID, char * payload_string) {
	char * next_line = payload_string;

	// Max LUT-Request-Line length: 21 per Value (line)
	// 3;127;4095;-3250.37\r\n
	char lut_request_line[22];
	uint8_t n = 0;
	do {
		next_line = getLine(next_line, lut_request_line);
		n++;
	} while (next_line);
	DAQ_ESP01_Send_Data(linkID, payload_string);
}

void handleKONFIGRequest(uint8_t linkID, char * payload_string) {
	char * next_value = payload_string;
	// Max KONFIG-Request length:
	// 0;"Temperatursensor1";"kg/m2";1;<float>;<float>\r\n

	DAQ_ESP01_Send_Data(linkID, payload_string);

//	char channel_id_string[2];
//	uint8_t channelID;
//	next_value = getNextCSVValue(next_value, channel_id_string);
//	channelID = channel_id_string[0] - '0';
//
//	// TODO: Remove leading and tailing "
//	next_value = getNextCSVValue(next_value, channel_konfig[channelID].short_name);
//
//	// TODO: Remove leading and tailing "
//	next_value = getNextCSVValue(next_value, channel_konfig[channelID].unit);
//
//	DAQ_ESP01_Send_Data(linkID, "OK");
}

int main(void) {
	UART_Init();
	//UART_PutString("Controller started!\r\n");

	init_debug_konfig();

	ioinit();
	DAQ_LCD_Init();

	DAQ_LCD_Update_Status("connecting...");

	init_timer();
	sei();
	start_timer();

	DAQ_MCP3204_Init();

	DAQ_set_ntc(channel_konfig[2].lut_number);
	DAQ_set_ldr(channel_konfig[1].lut_number);

	char ip_string[16];

	// Init ESP01 and put IP-Adress onto Display

	char received_data[1461];

	// Max. Response Length: 40 Byte per Channel
	// 0;"Temperatursensor1";"-3250.37 kg/m2"\r\n
	// Thus 4 x 40 + Termination Byte
	char response_data[161];

	if (DAQ_ESP01_Init()) {
		if (DAQ_ESP01_Query_IP(ip_string)) {
			DAQ_LCD_Update_IP(ip_string);
			UART_PutString(ip_string);

			DAQ_ESP01_Start_Server();
			DAQ_LCD_Update_Status("online");

			while (1) {
				if (DAQ_ESP01_Data_Received(received_data)) {
					//UART_PutString("data received!\r\n");
					//UART_PutString(received_data);

					// Disable Interrupts
					cli();

					char request_cmd[9];

					char * payload_string = getLine(received_data, request_cmd);

					if (!strcmp(request_cmd, "DATA")) {
						// Clear response data
						response_data[0] = 0;
						handleDATARequest(0, response_data);
					} else if (!strcmp(request_cmd, "KONFIG")) {
						handleKONFIGRequest(0, payload_string);
					} else if (!strcmp(request_cmd, "LUT")) {
						handleLUTRequest(0, payload_string);
					} else {
						DAQ_ESP01_Send_Data(0, "ERROR: WRONG REQUEST");
					}

					DAQ_ESP_01_Close_Connection(0);

					// Enable Interrupts
					sei();
				}
			}
		}
	}

	return 0;
}

ISR(TIMER1_COMPA_vect) {

	for (uint8_t id = 0; id < NUM_CHANNELS; id++) {
		if (channel_konfig[id].type != INACTIVE) {
			// Sample Channel and print the value onto LCD
			DAQ_MCP3204_Read_Channel(id, &channel_value[id]);

			// Calculate value
			if (channel_konfig[id].type == LINEAR) {
				channel_float[id] = channel_konfig[id].m * channel_value[id]
						+ channel_konfig[id].b;
				dtostrf(channel_float[id], 8, 2, channel_value_str[id]);
			} else {
				DAQ_value_from_lut(channel_konfig[id].lut_number,
						channel_value[id], &channel_float[id]);
				if (id == 2) {
					channel_float[2] = channel_float[2] - 5.0;
				}
				dtostrf(channel_float[id], 8, 2, channel_value_str[id]);
			}
			sprintf(channel_value_string[id], "%s %s", channel_value_str[id],
					channel_konfig[id].unit);
		} else {
			// Channel is inactive
			strcpy(channel_value_string[id], "n.c.");
		}
	}

	DAQ_LCD_Set_Channel(1, channel_value_string[0]);
	DAQ_LCD_Set_Channel(2, channel_value_string[1]);
	DAQ_LCD_Set_Channel(3, channel_value_string[2]);
	DAQ_LCD_Set_Channel(4, channel_value_string[3]);
	DAQ_LCD_Update();
}
