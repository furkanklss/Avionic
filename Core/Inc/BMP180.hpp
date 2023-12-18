#ifndef INC_BMP180_HPP_
#define INC_BMP180_HPP_

#include "i2c.h"

extern I2C_HandleTypeDef hi2c1;


class BMP180{
public:
	void BMP180_INIT(void); // INIT SENSOR AND READ CALIBRATION DATA
	uint16_t BMP180_RAW_TEMP(void); // READ TEMP REGISTERS
	float BMP180_CALCULATE_TEMP(void); // CALCULATE TEMP REGISTER AND OCCURS TEMPERATURE
	uint32_t BMP180_RAW_PRESS(int overSampling); // READ PRESS REGISTERS
	float BMP180_CALCULATE_PRESSURE(int overSampling); // CALCULATE PRESS REGISTER AND OCCURS PRESSURE
	float BMP180_CALCULATE_ALTITUDE(int overSampling); // OCCURS ALTITUDE
	long Pressure = 0;
	long Temperature = 0;

private:
	#define atmPress 101325  // PRESSURE PA
	#define BMP180_I2C &hi2c1 // I2C ADRESS
	#define BMP180_ADDRESS 0xEE // DEVICE ADRESS

	/*  FROM DATASHEET FOR CALCULATIONS */
	short AC1 = 0;
	short AC2 = 0;
	short AC3 = 0;
	unsigned short AC4 = 0;
	unsigned short AC5 = 0;
	unsigned short AC6 = 0;
	short B1 = 0;
	short B2 = 0;
	short MB = 0;
	short MC = 0;
	short MD = 0;
	long UT = 0;
	short oss = 0;
	long UP = 0;
	long X1 = 0;
	long X2 = 0;
	long X3 = 0;
	long B3 = 0;
	long B5 = 0;
	unsigned long B4 = 0;
	long B6 = 0;
	unsigned long B7 = 0;

};



#endif /* INC_BMP180_HPP_ */
