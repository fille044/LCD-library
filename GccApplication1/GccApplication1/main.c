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

#include <string.h>
#include <avr/io.h>
#include <util/delay.h>

void send_it(void) {
	ENABLE;
	_delay_us(500);
	DISABLE;
	_delay_us(500);
}

void print(char *input) {
	RS_SIGN;	
	int a = strlen(input); 
	for (int ix = 0; ix < a; ix++){
		PORTD = input[ix];
		send_it();
	}
}

void clear(void) {
	RS_INSTR;
	//Clear screen
	PORTD = 0x01;
	send_it();
}

void init(void) {
	DDRD = 0xFF;
	DDRB = 0xFF;
	_delay_ms(50);
	RS_INSTR;
	DISABLE;
	_delay_us(500);
	// Set 2 rows
	PORTD = 0b00111100;
	send_it();
	// Turn on screen
	PORTD = 0x0C;
	send_it();
	//Clear screen
	clear();
}

void set_cursor(int a, int b) {
	RS_INSTR;
	if (a==1){
		PORTD = 0x80 + b;
		send_it();
	}
	else if (a==2){
		PORTD = 0xC0 + b;
		send_it();
	}
}
	
int main(void) {
	init();
    while (1) {	
		set_cursor(1,0);
		print("Hello");
		set_cursor(2, 8);
		print("success");
		_delay_ms(500);
		clear();
	}
}




