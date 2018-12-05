/*
 * bno055.h
 *
 * Created: 12/3/2018 3:51:11 PM
 *  Author: Indrid
 */


#ifndef BNO055_H_
#define BNO055_H_

#include <stdint.h>
#include "TWI_Master.h"
#include "TWI_Slave.h"

#define BNO_ADR_LO 0x28
#define BNO_ADR_HI 0x29


#define OPR_MODE_REG 0X3D

typedef struct {
    int16_t x;
    int16_t y;
    int16_t z;
} BNO_Data;

BNO_Data getBNO055();
void changeModeBNO055();
void initBNO055();

#endif /* BNO055_H_ */