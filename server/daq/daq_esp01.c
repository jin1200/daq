/*
 * daq_esp01.c
 *
 */

#include <avr/io.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "daq_esp01.h"
#include "../dmm/uart.h"

#define MAX_CMD_RESPONSE_LINE 5

typedef struct {
	uint8_t lines;
	char line_string[MAX_CMD_RESPONSE_LINE][50];
} esp_response;

esp_response cmd_response;

void ESP01_UART_Init() {
	// UART1:

	// Set baud rate (115200 bit/s)
	UBRR1 = 8;

	// Enable receiver and transmitter
	UCSR1B = (1 << RXEN1) | (1 << TXEN1);

	// Frame Format: Asynchron 8N1
	UCSR1C = (1 << UCSZ01) | (1 << UCSZ00);
}

void ESP01_UART_Flush() {
	uint8_t dummy;
	while (UCSR1A & (1 << RXC1))
		dummy = UDR1;
}

void ESP01_UART_Transmit_Char(uint8_t data) {
	/* Wait for empty transmit buffer */
	while (!(UCSR1A & (1 << UDRE1)))
		;

	/* Put data into buffer, sends the data */
	UDR1 = data;
}

uint8_t ESP01_UART_Receive_Char() {
	/* Wait for data to be received */
	while (!(UCSR1A & (1 << RXC1)))
		;

	/* Get and return received data from buffer */
	return UDR1;
}

size_t ESP01_UART_Reveive_Line(char * line_string) {
	uint8_t i;
	// read until line-feed (LF = \n)
	while (1) {
		line_string[i] = ESP01_UART_Receive_Char();
		UART_PutChar(line_string[i]);
		if (line_string[i] == '\n' && line_string[i - 1] == '\r')
			break;
		i++;
	}
	// terminate with null-byte and delete termination bytes (\r\n)
	line_string[i - 1] = 0;
	// return length of the line (i-1)
	return i - 1;
}

void ESP01_Receive_Response() {

	for (cmd_response.lines = 0; cmd_response.lines < MAX_CMD_RESPONSE_LINE;
			cmd_response.lines++) {
		ESP01_UART_Reveive_Line(cmd_response.line_string[cmd_response.lines]);
		UART_PutChar(0);
		if (!strcmp(cmd_response.line_string[cmd_response.lines], "OK")) {
			// Response Line equals "OK"
			//UART_PutString("--- 'OK' empfangen!\r\n");
			cmd_response.lines++;
			break;
		} else if (!strcmp(cmd_response.line_string[cmd_response.lines],
				"ERROR")) {
			// Response Line equals "ERROR"
			//UART_PutString("--- 'ERROR' empfangen!\r\n");
			cmd_response.lines++;
			break;
		} else if (!strcmp(cmd_response.line_string[cmd_response.lines],
				"SEND OK")) {
			// Response Line equals "ERROR"
			//UART_PutString("--- 'ERROR' empfangen!\r\n");
			cmd_response.lines++;
			break;
		}
	}
}

void ESP01_UART_Transmit_String(const char *string) {
	// Send string without teminating null byte

	while (*string) {
		ESP01_UART_Transmit_Char(*string);
		string++;
	}
}

void ESP01_Send_Cmd(const char *cmd) {
	ESP01_UART_Transmit_String(cmd);
	ESP01_UART_Transmit_String("\r\n");
}

uint8_t ESP01_AT_Cmd_Echo(uint8_t value) {
	switch (value) {
	case 0:
		ESP01_Send_Cmd("ATE0");
		break;
	case 1:
		ESP01_Send_Cmd("ATE1");
		break;
	default:
		return 0;
		break;
	}
	ESP01_Receive_Response();
//	char response[100];
//	//UART_PutInteger(response);
//	ESP01_UART_Reveive_Line(response); // Read empty line
//	UART_PutString(response);
//	ESP01_UART_Reveive_Line(response); // Read response ("OK\r\n")
//	UART_PutString(response);
//	if (!strcmp(response, "OK")) {
//		return 1;
//	} else {
//		return 0;
//	}
	return 1;
}

void DAQ_ESP_01_Close_Connection(uint8_t link_id) {
	ESP01_UART_Transmit_String("AT+CIPCLOSE=");
	ESP01_UART_Transmit_Char(link_id + '0');
	ESP01_UART_Transmit_String("\r\n");
	ESP01_Receive_Response();
}

uint8_t DAQ_ESP01_Query_Current_Mode() {
	ESP01_Send_Cmd("AT+CWMODE_CUR?");
	ESP01_Receive_Response();
	return 1;
}

uint8_t DAQ_ESP01_Query_IP(char *ip_string) {
	ESP01_Send_Cmd("AT+CIPAP?");
	ESP01_Receive_Response();
	char * ip_index;
	if (cmd_response.lines > 4) {
		ip_index = strcasestr(cmd_response.line_string[cmd_response.lines - 5],
				"+CIPAP:ip:\"");
		if (ip_index != NULL) {
			strlcpy(ip_string, (ip_index + 11), (strlen(ip_index) - 11));
			return 1;
		} else {
			return 0;
		}
	} else {
		return 0;
	}
}

uint8_t DAQ_ESP01_Data_Received(char * received_data) {
	// Receive Header (e.g. '+IPD,0,1460:')
	char header_start;
	uint8_t link_id;
	uint16_t data_length;

	while (1) {
		header_start = ESP01_UART_Receive_Char();
		if (header_start == '+') {
			char cmd_name[4];
			uint8_t i;
			for (i = 0; i < 3; i++) {
				cmd_name[i] = ESP01_UART_Receive_Char();
			}
			// Terminate String
			cmd_name[i] = 0;

			if (!strcmp(cmd_name, "IPD")) {
				// Receive first comma
				ESP01_UART_Receive_Char();

				// Receive link id
				link_id = ESP01_UART_Receive_Char();

				// Convert received char to integer
				link_id -= '0';

				// Receive second comma
				ESP01_UART_Receive_Char();

				// Receive data length string
				uint8_t n;
				char data_length_char;
				char data_length_string[5];
				for (n = 0; n < 5; n++) {
					data_length_char = ESP01_UART_Receive_Char();
					if (data_length_char == ':') break;
					data_length_string[n] = data_length_char;
				}
				// Terminate String
				data_length_string[n] = 0;

				// Convert data_length_string to integer
				data_length = atoi(data_length_string);

				// TODO: Return linkID

				// Receive data_length chars
				uint16_t m;
				for (m = 0; m < data_length; m++) {
					received_data[m] = ESP01_UART_Receive_Char();
				}

				// Terminate String
				received_data[m] = 0;

				return 1;
			}
		}
	}

	return 1;
}

uint8_t DAQ_ESP01_Send_Data(uint8_t link_id, char * data) {
	uint16_t data_length = strlen(data);
	char data_length_string[5];
	sprintf(data_length_string, "%d", data_length);
	ESP01_UART_Transmit_String("AT+CIPSEND=");
	ESP01_UART_Transmit_Char(link_id + '0');
	ESP01_UART_Transmit_Char(',');
	ESP01_UART_Transmit_String(data_length_string);
	ESP01_UART_Transmit_String("\r\n");
	ESP01_Receive_Response();

	// Receive '>'
	char begin_transmission = ESP01_UART_Receive_Char();
	if (begin_transmission == '>') {
		// Begin to send data
		ESP01_UART_Transmit_String(data);
	}

	ESP01_Receive_Response();

	// TODO: Wait for complete transmission
	return 1;
}

uint8_t DAQ_ESP01_Start_Server() {
// Allow multiple connections (required for TCP-Server)
	ESP01_Send_Cmd("AT+CIPMUX=1");
	ESP01_Receive_Response();

// Start TCP-Server on port 80
	ESP01_Send_Cmd("AT+CIPSERVER=1,80");
	ESP01_Receive_Response();

	return 1;
}

uint8_t DAQ_ESP01_Init() {
	ESP01_UART_Init();

// Deactivate UART Echo
// If command response received, init is done correctly
	ESP01_AT_Cmd_Echo(DAQ_ESP01_ECHO_OFF);
	return 1;
}

