/*
 * daq_lcd.h
 *
 */

#ifndef DAQ_LCD_H_
#define DAQ_LCD_H_

void DAQ_LCD_Init();
void DAQ_LCD_Update_IP(const char *ip_string);
void DAQ_LCD_Update_Status(const char *status);
void DAQ_LCD_Update_Channel(uint8_t channel, const char *description);
void DAQ_LCD_Set_Channel(uint8_t channel, const char *description);
void DAQ_LCD_Update();

#endif /* DAQ_LCD_H_ */
