/*
 * GccApplication1.c
 *
 * Created: 04/04/2017 09:54:20
 * Author : fille
 */ 

/*	RS PB1
	E PB2
	D0 PD0
	D1 PD1
	D2 PD2
	D3 PD3
	D4 PD4
	D5 PD5
	D6 PD6
	D7 PD7
*/

#define F_CPU 1600000
#define ENABLE (PORTB |= (1<<PB2))
#define DISABLE (PORTB &=~(1<<PB2))
#define RS_SIGN (PORTB |= (1<<PB1))
#define RS_INSTR (PORTB &= ~(1<<PB1))

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRD = 0xFF;
	DDRB = 0xFF;
	_delay_ms(50);
	
	RS_INSTR;
	DISABLE;
	
	PORTD = 0x0C;
	ENABLE;
	_delay_ms(5);
	DISABLE;
	_delay_ms(5);
	
	PORTD = 0x01;
	ENABLE;
	_delay_ms(5);
	DISABLE;
	_delay_ms(5);
	
    while (1) 
    {
		RS_SIGN;
		PORTD = 0b00110011; // trea
		ENABLE;
		_delay_ms(5);
		DISABLE;
		_delay_ms(5);
	}
}




