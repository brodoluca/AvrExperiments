/*
 * GccApplication2.c
 *
 * Created: 25/05/2020 17:18:47
 * Author : utente
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>



int main(void)
{
    /* Using timer0 to generate a square wave on pinPORTB5 while at the same time transferring data from PORTC to PORTD */
    DDRB |= 0x20; //0b 0010 0000 DDRB.5 as output
	TCNT0 = -32; //timer value for 4 microseconds
	TCCR0 = 0x01; //Normal mode, no prescaler
	
	TIMSK = (1<<TOIE0); //enable Timer0 overflow interrupt
	sei();
	
	DDRC = 0x00;  // input
	DDRD = 0xFF; //output
	int counter = 7;
	
	
	while (1){ //wait here
		if (counter>10){
			PORTC = 0x12;
			counter=0;
				
		}else{
			PORTC = counter;
			counter++;
		}
		
		PORTD = PINC;
	}
}
ISR(TIMER0_OVF_vect){
	TCNT0 = -32;
	PORTB ^= 0x20; //toggle PORTB5
}
