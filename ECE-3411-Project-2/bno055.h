/*
 * bno055.h
 *
 * Created: 12/3/2018 3:51:11 PM
 *  Author: Indrid
 */ 


#ifndef BNO055_H_
#define BNO055_H_

#include <stdint.h>


typedef struct {
	int16_t x;
	int16_t y;
	int16_t z;
} BNO_DATA;

Vector getBNO055();
void changeMode();
void initBNO055();

#endif /* BNO055_H_ */