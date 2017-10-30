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


/* ------------------------------------------------------*/
/*
   Sends data in buffer to LCD
*/
/* ------------------------------------------------------*/
void sendItLcd(void) {
	ENABLE;
	_delay_us(500);
	DISABLE;
	_delay_us(500);
}


/* ------------------------------------------------------*/
/*
   Sets the cursor to where next sign should be placed
*/
/* ------------------------------------------------------*/
void set_cursorLcd(int a, int b) {
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


/* ------------------------------------------------------*/
/*
   Stores an integer in buffer to send
*/
/* ------------------------------------------------------*/
void printIntLcd(int input) {
	RS_SIGN
	char CharBuffer[10];
	sprintf(CharBuffer, "%d", input);
	int a = strlen(input);
	for (int ix = 0; ix < a; ix++){
		PORTD = CharBuffer[ix];
		send_it();
	}
}


/* ------------------------------------------------------*/
/*
   Stores an char array in buffer to send
*/
/* ------------------------------------------------------*/
void printCharLcd(char *input) {
	RS_SIGN;
	int a = strlen(input);
	for (int ix = 0; ix < a; ix++){
		PORTD = input[ix];
		send_it();
	}
}


/* ------------------------------------------------------*/
/*
   Clears screen
*/
/* ------------------------------------------------------*/
void clearLcd(void) {
	RS_INSTR;
	PORTD = 0x01;
	send_it();
}


/* ------------------------------------------------------*/
/*
   Initialize LCD with special LCD-commands
*/
/* ------------------------------------------------------*/
void initLcd(void) {
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


/* ------------------------------------------------------*/
/*
   Main loop
*/
/* ------------------------------------------------------*/
int main(void) {
	initLcd();
    while (1) {
		set_cursorLcd(1,0);
		printCharLcd("Hello");
		set_cursorLcd(2, 8);
		printCharLcd("success");
		_delay_ms(500);
		clearLcd();
	}
}
