/*
 * Blink_LED.cpp
 *
 *  Created on: Sep 25, 2013
 *      Author: lhotse
 */
//#include <stdio.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>



ISR(TIMER1_COMPA_vect)
{
	// Toggle the LED
	PORTB ^= (1 << PORTB5);
}



int main( void )
{
	// Set Port B direction Register
	DDRB |= (1<<DDB5) ; // For LED on Pin PORTB5

	// Configure the Timer/Counter1 Control Register A
	TCCR1A = 0 ;
	// Configure the Timer/Counter1 Control Register B
	TCCR1B = (1 << WGM12) ; // Configure timer 1 for CTC mode

	TIMSK1 = (1 << OCIE1A); // Enable CTC interrupt

	OCR1A   = 15624 ; // Set CTC compare value to 1Hz at 1MHz AVR clock, with a prescaler of 64

	sei(); //  Enable global interrupts

	TCCR1B |= (1 << CS12) ; // Start timer at Fcpu/64

	while( 1 )
	{
		sleep_mode();
	}

	return( 0 ) ;
}


