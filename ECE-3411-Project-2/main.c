/*
 * ECE-3411-Project-2.c
 *
 * Created: 12/3/2018 2:50:21 PM
 * Author : nodcah
 */

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <math.h>
#include "uart.h"
#include "bno055.h"

// multiplying factor for bno data to radians (2*pi)/(360*16)
#define DATA_TO_RAD 0.00109082986

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
    initTimers();
    uart_init();
    //initBNO055();
    sei();
    printf("Init\n");

    while (1) {
        if (readFlag) {
            printf("Reading\n");
            readFlag=0;
            double speed = getPotentiometer();
            BNO_Data data = {1000, 0, 0};//getBNO055();
            printf("Pot: %.5f\n", speed);

            // Send data out to computer via UART
            double dx = speed*sin(((double)data.x)*DATA_TO_RAD);
            double dy = speed*cos(((double)data.x)*DATA_TO_RAD);
            double dz = speed*sin(((double)data.y)*DATA_TO_RAD);
            putchar(0x78);
            putDouble(dx);
            putDouble(dy);
            putDouble(dz);
        }
    }
}

void initTimers() {
    // Timer 1: CTC mode, 200 ms
    TCCR1B |= (1<<WGM12);  // Clear on Compare A
    OCR1A = 12500;          // Set number of ticks for Compare A
    TIMSK1 = (1<<OCIE1A);  // Enable Timer 1 Compare A ISR
    TCCR1B |= 4;           // Set Prescalar & Timer 1 starts
}

void initIO() {
    // init ADC
    ADMUX |= 1<<MUX2 | 1<<MUX1;  // Use ADC 6
    // Enable ADC and set prescalar to 128
    ADCSRA |= 1<<ADEN | 1<<ADPS0 | 1<<ADPS1 | 1<<ADPS2;
}

void putDouble(double x) {
    uint8_t *ptr = (uint8_t *)&x;
    for (int i=0; i<sizeof(double); i++) {
        putchar(ptr[i]);
    }
}

double getPotentiometer() {
    // Read pot value to get speed
    ADCSRA |= 1<<ADSC;  // Start conversion
    while ((ADCSRA & (1<<ADSC)) != 0);  // Wait for read
    int input = ADC;  // Read registers
    return (((double)input)/1023.0);  // return as double between 0 and 1
}
