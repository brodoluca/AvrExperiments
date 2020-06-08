/*
 * GccApplication1.c
 *
 * Created: 24/05/2020 13:43:00
 * Author : utente
 */ 

#include <avr/io.h>
#include <stdio.h>
void delay100ms(void){
	unsigned int i;
	for (i=0; i<42150;i++);
}

void T0Delay(); //internal clock


int main(void){	
	DDRD = 0xFF;
	while (1){
		PORTD = 0b11111111;
		T0Delay();
		//PORTB = 0x0;
		//T0Delay();
		PORTD = 0b00000000; //0b 1010 1010
		T0Delay();
	}
	
	/*
	__________DELAY TIMER_________
	
	XTAL = 8Mhz -> Tmachine_cycle = 1/8Mhz
	Prescaler 1:8 -> Tclock=8*1/8Mhz= 1us, microse
	70microsecond / 1microsecond = 70 ticks -> 1+255 -70= 186
	
	
	*/
	/*
	//printf("%f", kaan);
	DDRB = 0xFF;
	while(1){
		T0Delay(70);
		PORTB = ~PORTB;
		luca++;
	}
	*/
	
	
	
	/*
	//-------FIRST DELAY--------
	DDRB = 0xFF; //output port 0b1111 1111
	while(1){
		PORTB = 0x55; //0b 0101 0101
		T0Delay();
		//PORTB = 0x0;
		//T0Delay();
		PORTB = 0xAA; //0b 1010 1010
		T0Delay();
	} */
	
	
	
	
	
	/*
	int var=7;
	//0000 0001 -> 1000 0000
	DDRB = ~(1<<7); //0b0111 1111
	while(1)
		if (PINB & (1<<var)) //0b1000 0000
			DDRB &= ~(1<<4); //0b1110 1111
		else
			DDRB |= (1<<4); //0b0001 0000
	
	
	
	
	------BIT INVERTER--------
	PORTB = 0xFF;
	PORTB = 0xAA; //0b 1010 1010
	//----XOR-----//
	while(1)
		PORTB^=OxFF;
	
	//----Inv---//
	while(1)
		PORTB ~=PORTB;
	*/
	/*
	//------BIT ASSIGNMENT ÒTHER PORT---------
	DDRB = 0xEF;//1101 1111
	DDRC = 0x7F; //0b0111 1111
	while(1){
		if(PINB & ~0xEF) //0xEF = 1101 1111, 0010 0000 . 0000 0000
			PORTC |= 0x80; //0b1000 0000
		else
			PORTC &= 0x7F;//0b0111 1111
	}	*/
	
	
	
	
	/*
	--------BIT ASSIGNER SAME PORT----------
	DDRB =	0x7F;	//0b0111 1111;
	while(1)
		if(PINB&0x80) //0b	1000	0000
			DDRB &=0xEF;	//0b1110	1111
		else
			DDRB |=0x10;   //0b0001 0000
	
	*/
	/*
	//----------------BITMASKING
	unsigned char receivedChar;
	DDRB=0x0; //as input
	DDRD=0xFF; //as output
	while(1){
		
		receivedChar = PINB; // 0000 0000
		receivedChar &= 0x03; //mask the last two bits, 0b00000011 
		
		//0000 0000 0
		//0000 0001 1
		//0000 0010 2
		//0000 0011 3
		
		pin0 and(1)		pin1 and 
			1		1		 0	  0
			0		0		 1	  1
			
			00 0
			01 1
			10 2
			11	3				
		
		//PORTD = (char)receivedChar;
		switch(receivedChar){
			case 0: PORTC=0x1F; break;
			case 1: PORTC='1';break;
			case 2: PORTC='2';break;
			case 3: PORTC='3';break;
		}
		
	}
	
	*/
	
	
	
	
	/*
	---------------LCD COMMUNICATION---------------
		unsigned char message[]="LUCA BRODO";
		unsigned char counter;
		DDRB = 0xFF; //portb is output. all pins
		DDRC |= 0x20; //pin5 of port c is output
		for (counter=0;counter<10;counter++){
			PORTB = message[counter];
			PORTC |= 0x20;	
			PORTC &= 0xDF;
		
		}
		while (1);
		---------------LED ON OFF-------------------
		DDRB &=0b11111101; //pin 1 of portB is input
		DDRC |= 0b10000000; //pin 7 of portC is output
		if (PINB&0b00000010) PORTC|=0b10000000; //pin7 to high
		else				 PORTC&=0b01111111; //pin7 low
		*/
	return 0;
}
void T0Delay(){
	/*
	XTAL = 8Mhz -> Tmachine_cycle = 1/8Mhz
	Prescaler 1:8 -> Tclock=8*1/8Mhz= 1us, microse
	70microsecond / 1microsecond = 70 ticks -> 1+255 -70= 186
	
	Prescaler 1:64 -> 64*1/8 = 8ms
	70ms / 8
	Tclock = 1/(16)*prescaler value
	256 - delay *10^-3/Tclock
	
	
	*/
	
	/*
	
	TCNT0 = 255 +1 - milliseconds/8; //we decide the value to reach here
	
	
	TCCR0 = 0x03; //normal mode with a prescaler //this is the control register
	while((TIFR&(1<<TOV0))==0); //TIFR contains OCF0, the second bit, which is the output conpare bit and is set whenTCNT and OCR are equal. BasicalLY OCR counts up till is equal to TCNT and set the flaf
	//while(~TOV0);
	TCCR0 =0;
	TIFR=0x1;
	*/
	
	
	TCNT0 = 0x20;
	TCCR0 = 0x01; //Timer 0, Normal mode, no prescaler
	while((TIFR&0x1)==0); //until it rolls over, it sets when overlows, than 11 no more zero
	TCCR0=0;
	TIFR = 0x1;
	
}