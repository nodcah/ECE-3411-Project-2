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
#define BNO_ADR BNO_ADR_LO


#define OPR_MODE_REG 0x3D
#define OPR_MODE_IMU 0x8

#define ACC_DATA_XLO_REG 0x08
#define ACC_DATA_XHI_REG 0x09
#define ACC_DATA_YLO_REG 0x0A
#define ACC_DATA_YHI_REG 0x0B
#define ACC_DATA_ZLO_REG 0x0C
#define ACC_DATA_ZHI_REG 0x0D

#define EUL_DATA_XLO_REG 0x1A
#define EUL_DATA_XHI_REG 0x1B
#define EUL_DATA_YLO_REG 0x1C
#define EUL_DATA_YHI_REG 0x1D
#define EUL_DATA_ZLO_REG 0x1E
#define EUL_DATA_ZHI_REG 0x1F

typedef struct {
    int16_t x;
    int16_t y;
    int16_t z;
} BNO_Data;

BNO_Data getBNO055();
void changeModeBNO055(uint8_t);
void initBNO055();

#endif /* BNO055_H_ */