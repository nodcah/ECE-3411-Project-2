/*
 * bno055.c
 *
 * Created: 12/3/2018 3:50:59 PM
 *  Author: Indrid
 */

#include <avr/io.h>
#include "bno055.h"
#include "twi.h"

BNO_Data getBNO055() {
	BNO_Data data;
	
	startTWI1();
	writeTWI1((BNO_ADR << 1) | TWI_WRITE);
	writeTWI1(ACC_DATA_XLO_REG);
	writeTWI1((BNO_ADR << 1) | TWI_READ);
	data.x = readAckTWI1();
	data.x |= ((int16_t) readAckTWI1()) << 8;
	data.y = readAckTWI1();
	data.y |= ((int16_t) readAckTWI1()) << 8;
	data.z = readAckTWI1();
	data.z |= ((int16_t) readNoAckTWI1()) << 8;
	stopTWI();
	
	return data;
}

void changeModeBNO055(uint8_t mode) {
	startTWI1();
	writeTWI1((BNO_ADR << 1) | TWI_WRITE);
	writeTWI1(OPR_MODE_REG);
	writeTWI1(mode);
	stopTWI();
}

void initBNO055() {
	initTWI1();
	
    changeModeBNO055(OPR_MODE_IMU);
}