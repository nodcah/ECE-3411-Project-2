/*
 * ECE-3411-Project-2.c
 *
 * Created: 12/3/2018 2:50:21 PM
 * Author : nodcah
 */

#include <avr/io.h>
#include "TWI_Master.h"
#include "TWI_Slave.h"
#include "uart.h"

#define I2C_ADDRESS 0x28

typedef struct {
    int x = 0;
    int y = 0;
    int z = 0;
} Vector;

uint8_t readFlag = 0;  // Flag to determine when to read

void initIO();
void initTimers();
void TWI_Master_Initialize();

// Timer1 ISR
ISR(TIMER1_COMPA_vect) {
    readFlag=1;
}

int main(void) {
    initIO();
    uart_init();
    TWI_Master_Initialize();
    sei();
    printf("Init\n");

    while (1) {
		
    }
}

void TWI_Master_Initialize() {
    TWBR1 = 32;  // bit rate
}

void initTimers() {
    // Timer 1: CTC mode, 200 ms
    TCCR1B |= (1<<WGM12);  // Clear on Compare A
    OCR1A = 5000;          // Set number of ticks for Compare A
    TIMSK1 = (1<<OCIE1A);  // Enable Timer 1 Compare A ISR
    TCCR1B |= 4;           // Set Prescalar & Timer 1 starts
}

void initIO() {
    // Nothing for now
}

Vector TWI_Receive_xyz(uint8_t Address) {
    //====================== WRITE COMMAND ========================
    TWCR1 = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN); // Send START condition
    while (!(TWCR1 & (1<<TWINT))); // Wait for TWINT Flag set.
    TWDR1 = (Address << 1); // Load SLA_W (Slave Address & Write) into TWDR.
    TWCR1 = (1<<TWINT) | (1<<TWEN); // Clear TWINT to start address transmission.
    while (!(TWCR1 & (1<<TWINT))); // Wait for TWINT Flag set.
    TWDR1 = 0; // Load COMMAND=0 into TWDR
    TWCR1 = (1<<TWINT) | (1<<TWEN); // Clear TWINT bit to start transmission of data.
    while (!(TWCR1 & (1<<TWINT))); // Wait for TWINT Flag set.

    //TWCR = (1<<TWINT)|(1<<TWEN)| (1<<TWSTO); // Transmit STOP condition.

    //====================== Read TEMP ========================
    TWCR1 = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN); // Send START condition
    while (!(TWCR1 & (1<<TWINT))); // Wait for TWINT Flag set.
    TWDR1 = (Address << 1) | (1); // Load SLA_W (Slave Address & READ) into TWDR.
    TWCR1 = (1<<TWINT) | (1<<TWEN); // Clear TWINT to start address transmission.
    while (!(TWCR1 & (1<<TWINT))); // Wait for TWINT Flag set.
    //TWDR = Data; // Load DATA into TWDR Register.
    TWCR1 = (1<<TWINT) | (1<<TWEN); // Clear TWINT bit to start receiving data.
    while (!(TWCR1 & (1<<TWINT))); // Wait for TWINT Flag set.

    TWCR1 = (1<<TWINT)|(1<<TWEN)| (1<<TWSTO); // Transmit STOP condition.
    return TWDR1;
}

