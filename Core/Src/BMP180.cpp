#include "BMP180.hpp"
#include "math.h"

void BMP180::BMP180_INIT(void){
	uint8_t calibrationDatas[22] = {0};
	uint16_t calibrationStart = 0xAA;

	HAL_I2C_Mem_Read(BMP180_I2C, BMP180_ADDRESS, calibrationStart, 1, calibrationDatas, 22, HAL_MAX_DELAY);
	AC1 = ((calibrationDatas[0] << 8) | calibrationDatas[1]);
	AC2 = ((calibrationDatas[2] << 8) | calibrationDatas[3]);
	AC3 = ((calibrationDatas[4] << 8) | calibrationDatas[5]);
	AC4 = ((calibrationDatas[6] << 8) | calibrationDatas[7]);
	AC5 = ((calibrationDatas[8] << 8) | calibrationDatas[9]);
	AC6 = ((calibrationDatas[10] << 8) | calibrationDatas[11]);
	B1 = ((calibrationDatas[12] << 8) | calibrationDatas[13]);
	B2 = ((calibrationDatas[14] << 8) | calibrationDatas[15]);
	MB = ((calibrationDatas[16] << 8) | calibrationDatas[17]);
	MC = ((calibrationDatas[18] << 8) | calibrationDatas[19]);
	MD = ((calibrationDatas[20] << 8) | calibrationDatas[21]);
}

uint16_t BMP180::BMP180_RAW_TEMP(void){
	uint8_t writeData = 0x2E;
	uint8_t tempData[2] = {0};
	HAL_I2C_Mem_Write(BMP180_I2C, BMP180_ADDRESS, 0xF4, 1, &writeData, 1, 1000);
	HAL_Delay (5);  // wait 4.5 ms for calculation from datasheet
	HAL_I2C_Mem_Read(BMP180_I2C, BMP180_ADDRESS, 0xF6, 1, tempData, 2, 1000);
	return ((tempData[0] << 8) + tempData[1] );
}

float BMP180::BMP180_CALCULATE_TEMP(void){
	/* CALCULATE FORMULA FROM DATASHEET */

	UT = BMP180_RAW_TEMP();
	X1 = ((UT-AC6) * (AC5/(pow(2,15))));
	X2 = ((MC*(pow(2,11))) / (X1+MD));
	B5 = X1+X2;
	Temperature = (B5+8)/(pow(2,4));
	return Temperature/10.0;
}

uint32_t BMP180::BMP180_RAW_PRESS(int overSampling){

	// OVERSAMPLING 0,1,2,3
	// OVERSAMPLING PRECISION VALUE MEASURING SETTING

	uint8_t writeData = 0x34 + (overSampling << 6);
	uint8_t pressData[3] = {0};
	HAL_I2C_Mem_Write(BMP180_I2C, BMP180_ADDRESS, 0xF4, 1, &writeData, 1, 1000);
	switch (overSampling)
	{
		case (0):
			HAL_Delay (5);
			break;
		case (1):
			HAL_Delay (8);
			break;
		case (2):
			HAL_Delay (14);
			break;
		case (3):
			HAL_Delay (26);
			break;
	}
	HAL_I2C_Mem_Read(BMP180_I2C, BMP180_ADDRESS, 0xF6, 1, pressData, 3, 1000);
	return ((( pressData[0] << 16 ) + ( pressData[1] << 8 ) + pressData[2] ) >> ( 8 - overSampling ));
}

float BMP180::BMP180_CALCULATE_PRESSURE(int overSampling){
	/* CALCULATE FORMULA FROM DATASHEET */
	// OVERSAMPLING 0,1,2,3
	// OVERSAMPLING PRECISION VALUE MEASURING SETTING

	UP = BMP180_RAW_PRESS(overSampling);
	X1 = ((UT-AC6) * (AC5/(pow(2,15))));
	X2 = ((MC*(pow(2,11))) / (X1+MD));
	B5 = X1+X2;
	B6 = B5-4000;
	X1 = (B2 * (B6*B6/(pow(2,12))))/(pow(2,11));
	X2 = AC2*B6/(pow(2,11));
	X3 = X1+X2;
	B3 = (((AC1*4+X3)<<overSampling)+2)/4;
	X1 = AC3*B6/pow(2,13);
	X2 = (B1 * (B6*B6/(pow(2,12))))/(pow(2,16));
	X3 = ((X1+X2)+2)/pow(2,2);
	B4 = AC4*(unsigned long)(X3+32768)/(pow(2,15));
	B7 = ((unsigned long)UP-B3)*(50000>>oss);
	if (B7<0x80000000) Pressure = (B7*2)/B4;
	else Pressure = (B7/B4)*2;
	X1 = (Pressure/(pow(2,8)))*(Pressure/(pow(2,8)));
	X1 = (X1*3038)/(pow(2,16));
	X2 = (-7357*Pressure)/(pow(2,16));
	Pressure = Pressure + (X1+X2+3791)/(pow(2,4));
	return Pressure;
}

float BMP180::BMP180_CALCULATE_ALTITUDE(int overSampling){
	/* CALCULATE FORMULA FROM DATASHEET */
	// OVERSAMPLING 0,1,2,3
	// OVERSAMPLING PRECISION VALUE MEASURING SETTING

	BMP180_CALCULATE_PRESSURE (overSampling);
	return 44330*(1-(pow((Pressure/(float)atmPress), 0.19029495718)));
}

