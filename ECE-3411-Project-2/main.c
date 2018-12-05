/*
 * ECE-3411-Project-2.c
 *
 * Created: 12/3/2018 2:50:21 PM
 * Author : nodcah
 */

#include <avr/io.h>
#include "uart.h"

typedef struct {
    int x = 0;
    int y = 0;
    int z = 0;
} Vector;

uint8_t readFlag = 0;  // Flag to determine when to read

void initIO();
void initTimers();
void putDouble(double x);
double getPotentiometer();

// Timer1 ISR
ISR(TIMER1_COMPA_vect) {
    readFlag=1;
}

int main(void) {
    initIO();
    uart_init();
    initBNO055();
    sei();
    printf("Init\n");

    while (1) {
        if (readFlag) {
            readFlag=0;
            getPotentiometer();
            BNO_Data data = getBNO055();

            // Send data out to computer via UART

        }
    }
}

void initTimers() {
    // Timer 1: CTC mode, 200 ms
    TCCR1B |= (1<<WGM12);  // Clear on Compare A
    OCR1A = 5000;          // Set number of ticks for Compare A
    TIMSK1 = (1<<OCIE1A);  // Enable Timer 1 Compare A ISR
    TCCR1B |= 4;           // Set Prescalar & Timer 1 starts
}

void initIO() {
    // init ADC
}

void putDouble(double x) {
    uint8_t *ptr = (uint8_t *)&x;
    for (int i=0; i<sizeof(double); i++) {
        putchar(ptr[i]);
    }
}

void getPotentiometer() {
    //TODO implement all ADC stuff
}
