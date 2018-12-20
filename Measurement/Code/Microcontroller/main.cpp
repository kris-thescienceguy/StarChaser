/*
 * EEPROM_Dump.cpp
 *
 * Created: 18/12/2018 16:23:59
 * Author : krist
 */ 
#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "BasicSerial3.h"

/*
* Pin Definitions
*
* P0 Phase A
* P1 Phase B
* P2 Home
* P3 Serial
* P4 Movement LED
* P5 Reset
*
*/

const signed int encoderDirections[] = {0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0};
volatile long encCount = 0;
volatile int noMovement = 0;

int main(void)
{
	DDRB = (1 << 3 ); // DDRB = 0011 1000
	PORTB |= (7 << 3); // Flash LEDs (sets P4 to pull up resistor)
	
	bool waitingForStartByte = true;
	
	while (waitingForStartByte){
		if (RxByte() == 's'){
			waitingForStartByte = false;
		}
	}
	
	PORTB &= (0 << 0); // PORTB = 0000 0000 to set pull up resistors off, and set all outputs to zero
	
	GIMSK |= (1 << 5);     // turns on pin change interrupts by setting bit 5 of GIMSK to 1
	GIMSK |= (1 << 6);   // turns on external interrupts
	PCMSK |= (3 << 0);   // set pin change interrupts on pins 0 and 1. Decimal 3 = Binary 11

	/*
	MCUCR Register: ISC0[1:0]: Interrupt Sense Control 0 Bit 1 and Bit 0
	0 0 The low level of INT0 generates an interrupt request.
	0 1 Any logical change on INT0 generates an interrupt request.
	1 0 The falling edge of INT0 generates an interrupt request. <=== This is what we want.
	1 1 The rising edge of INT0 generates an interrupt request.
	*/
	
	MCUCR |= (1 << 1);
	MCUCR &= ~(1 << 0);

	sei();                     // turn on interrupts

	
    /* Replace with your application code */
	
    while (1) 
    {
		//home = ((PINB >> 3) & 1); // Get state of home pin (shifts to LSB and then sets the rest of the array to 0)
		//encCount = encCount * home; // Home is default at 1 until pulled to ground by pin.
		noMovement += 1;
		
		if (noMovement > 5000){
			PORTB &= ~(1 << 4);	
		}
		
		// Transmit value out
		int numberOfBytes = (encCount / 255) + 1;
		for (int byteIndex = 0; byteIndex < numberOfBytes; byteIndex++)	{
			int shiftIndex = (numberOfBytes - byteIndex - 1)*8;
			int transmitByte = (encCount >> shiftIndex) & 255; // Ensures only first 8 bits have value
			TxByte(transmitByte);
		}
		TxByte('#');
    }
}

/* Pin Change Interrupts */
ISR (PCINT0_vect) {
	static unsigned int oldEncoderState = 0;
	
	oldEncoderState <<= 2;
	oldEncoderState |= (PINB & 0x03);
	encCount += encoderDirections[(oldEncoderState & 0x0F)];
	PORTB |= (1 << 4);
	noMovement = 0;

}

/* External Interrupt - takes priority */
ISR (INT0_vect) {
	noMovement = 0;
	PORTB |= (1 << 4);
	encCount = 0;	
}