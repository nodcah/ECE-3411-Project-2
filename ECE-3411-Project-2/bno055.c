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
    //====================== WRITE COMMAND ========================
    TWCR1 = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN); // Send START condition
    while (!(TWCR1 & (1<<TWINT))); // Wait for TWINT Flag set.
    TWDR1 = (I2C_ADDRESS << 1); // Load SLA_W (Slave Address & Write) into TWDR.
    TWCR1 = (1<<TWINT) | (1<<TWEN); // Clear TWINT to start address transmission.
    while (!(TWCR1 & (1<<TWINT))); // Wait for TWINT Flag set.
    TWDR1 = 0; // Load COMMAND=0 into TWDR
    TWCR1 = (1<<TWINT) | (1<<TWEN); // Clear TWINT bit to start transmission of data.
    while (!(TWCR1 & (1<<TWINT))); // Wait for TWINT Flag set.

    //TWCR = (1<<TWINT)|(1<<TWEN)| (1<<TWSTO); // Transmit STOP condition.

    //====================== Read TEMP ========================
    TWCR1 = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN); // Send START condition
    while (!(TWCR1 & (1<<TWINT))); // Wait for TWINT Flag set.
    TWDR1 = (I2C_ADDRESS << 1) | (1); // Load SLA_W (Slave Address & READ) into TWDR.
    TWCR1 = (1<<TWINT) | (1<<TWEN); // Clear TWINT to start address transmission.
    while (!(TWCR1 & (1<<TWINT))); // Wait for TWINT Flag set.
    //TWDR = Data; // Load DATA into TWDR Register.
    TWCR1 = (1<<TWINT) | (1<<TWEN); // Clear TWINT bit to start receiving data.
    while (!(TWCR1 & (1<<TWINT))); // Wait for TWINT Flag set.

    TWCR1 = (1<<TWINT)|(1<<TWEN)| (1<<TWSTO); // Transmit STOP condition.
    return TWDR1;
	
	
	
}

void changeModeBNO055() {
	
}

void initBNO055() {
    initTWI1();
	writeTWI1((BNO_ADR_LO << 1) | 0);
	
}