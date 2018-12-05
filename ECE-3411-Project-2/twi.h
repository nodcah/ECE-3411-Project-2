/*
 * twi.h
 *
 * Created: 12/5/2018 3:06:32 PM
 *  Author: Indrid
 */ 


#ifndef TWI_H_
#define TWI_H_

#include <stdint.h>

void initTWI1();
void startTWI1();
uint8_t writeTWI1(uint8_t data);
void waitTWI1();
void stopTWI();
uint8_t readAckTWI1();
uint8_t readNoAckTWI1();

#endif /* TWI_H_ */