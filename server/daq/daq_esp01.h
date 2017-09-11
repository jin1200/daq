/*
 * daq_esp01.h
 */

#ifndef DAQ_ESP01_H_
#define DAQ_ESP01_H_

#define DAQ_ESP01_ECHO_ON	1
#define DAQ_ESP01_ECHO_OFF	0
#define DAQ_ESP01_CWMODE_STATION		1
#define DAQ_ESP01_CWMODE_SOFTAP			2
#define DAQ_ESP01_CWMODE_SOFT_STAION	3

uint8_t DAQ_ESP01_Init();
uint8_t DAQ_ESP01_Query_IP(char *ip_string);
uint8_t DAQ_ESP01_Query_Current_Mode();
uint8_t DAQ_ESP01_Start_Server();
void DAQ_ESP_01_Close_Connection(uint8_t link_id);
uint8_t DAQ_ESP01_Send_Data(uint8_t link_id, char * data);
uint8_t DAQ_ESP01_Data_Received();

#endif /* DAQ_ESP01_H_ */
