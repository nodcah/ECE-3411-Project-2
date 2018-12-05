/*
 * twi.c
 *
 * Created: 12/5/2018 3:06:44 PM
 *  Author: Indrid
 */ 

#include <avr/io.h>
#include "twi.h"


#define BNO_ADR_LO 0x28 
#define BNO_ADR_HI 0x29

#define getState(port, bit) (port & (1<<bit))
#define setState(port, bit) (port |= (1<<bit))
#define clearState(port, bit) (port &= ~(1<<bit))

void initTWI1() {
	TWBR1 = 32; // Fscl = 200kHz given that PS = 1
	TWCR1 |= (1<<TWEN); // Enable I2C1 peripheral
}

void startTWI1() {
	TWCR1 = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN); // Send START condition
	waitTWI1();
}

uint8_t writeTWI1(uint8_t data) {
	TWDR1 = data;
	TWCR1 = (1<<TWINT) | (1<<TWEN);
	waitTWI1();
}

void waitTWI1() {
	while(!getState(TWCR1, TWINT)); // Wait for TWINT flag to be set
}

void stopTWI() {
	TWCR1 = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO); // Send STOP bit
}

uint8_t readAckTWI1() {
	TWCR1 = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	waitTWI1();
	return TWDR1;
}

uint8_t readNoAckTWI1() {
	TWCR1 = (1<<TWINT) | (1<<TWEN);
	waitTWI1();
	return TWDR1;
}