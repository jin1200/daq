/*
 * daq_lut.h
 *
 */

#ifndef BIB_DAQ_LUT_H_
#define BIB_DAQ_LUT_H_

#define LUT_GROESSE 						128

void DAQ_set_lut(uint8_t lut_id, uint8_t row, float x_value, float y_value);

void DAQ_lut_ntc(uint16_t adc_value, float *result);

void DAQ_value_from_lut(uint8_t lut_id, uint16_t adc_value, float *result);

void DAQ_calc_value(float *lut_x, float *lut_y, uint16_t adc_value,
		float *result);

void DAQ_set_ldr(uint8_t lut_id);
void DAQ_set_ntc(uint8_t lut_id);

#endif /* BIB_DAQ_LUT_H_ */
