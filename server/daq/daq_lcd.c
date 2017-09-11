/*
 * daq_lcd.c
 *
 */

#include <stdint.h>

#include "daq_lcd.h"
#include "../dmm/lcd.h"

void DAQ_LCD_Init() {
	LCD_Init();
	LCD_Clear();
	Backlight_LED(BL_RED_ON | BL_BLUE_ON | BL_GREEN_ON);

	LCD_PutString("IP:\r\n");
	LCD_PutString("Status:\r\n");
	LCD_PutString("\r\n\r\n");
	LCD_PutString("Ch1: n.c.\r\n");
	LCD_PutString("Ch2: n.c.\r\n");
	LCD_PutString("Ch3: n.c.\r\n");
	LCD_PutString("Ch4: n.c.");
	LCD_Update();
}

void DAQ_LCD_Update_IP(const char *ip_string) {
	// Max. Length IP String: 17

	// First clear current ip address
	LCD_GotoXY(4, 0);
	LCD_PutString("                 ");

	// Then add new ip address
	LCD_GotoXY(4, 0);
	LCD_PutString(ip_string);
	LCD_Update();
}

void DAQ_LCD_Update_Status(const char *status) {
	// Max. Length Status String: 13

	// First clear status line
	LCD_GotoXY(8, 1);
	LCD_PutString("             ");

	// Then write new status
	LCD_GotoXY(8, 1);
	LCD_PutString(status);
	LCD_Update();
}

void DAQ_LCD_Update_Channel(uint8_t channel, const char *description) {
	// Max. Length Channel Description: 16

	if (channel > 0 && channel < 5) {
		// only update LCD if the channel is valid (1..4)
		uint8_t channel_y = channel + 3;

		// First clear corresponding description line
		LCD_GotoXY(5, channel_y);
		LCD_PutString("                 ");

		// Then add new description
		LCD_GotoXY(5, channel_y);
		LCD_PutString(description);
		LCD_Update();
	}
}

void DAQ_LCD_Set_Channel(uint8_t channel, const char *description) {
	// Max. Length Channel Description: 16

	if (channel > 0 && channel < 5) {
		// only update LCD if the channel is valid (1..4)
		uint8_t channel_y = channel + 3;

		// First clear corresponding description line
		LCD_GotoXY(5, channel_y);
		LCD_PutString("                 ");

		// Then add new description
		LCD_GotoXY(5, channel_y);
		LCD_PutString(description);
	}
}

void DAQ_LCD_Update() {
	LCD_Update();
}
