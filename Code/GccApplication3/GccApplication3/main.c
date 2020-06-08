/*
 * GccApplication3.c
 *
 * Created: 25/05/2020 17:50:17
 * Author : utente
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

int main(void)
{
    /* Using timer= and TImer1 interrupts, generate sqaure waves on pins PB1 and PB7 respectively. while transferring data from PORTc and PORTD */
	DDRB |= 0x82;
	DDRC = 0x00;
	DDRD = 0xFF;
	
	TCNT0 = -160;
	TCCR0 = 0x01;
	
	TCNT1H = -640>>8;
	TCNT1L = -640;
	TCCR1A = 0x00;
	TCCR1B = 0x01;
	
	TIMSK = (1<<TOIE0) | (1<<TOIE1);
	sei();
	
	while(1)
		PORTD = PORTC;
}

ISR(TIMER0_OVF_vect){
	TCNT0 = -160; //reload
	PORTB ^= 0x02; //toggle second port
}
ISR(TIMER1_OVF_vect){
	TCNT1H = -640>>8;
	TCNT1L = -640;
	
	PORTB ^= 0x80;
}