/*********************************************
* Chip type           : ATTINY461
*********************************************/

#define F_CPU 8000000UL  // 8.0 MHz

#define _BV(bit) (1 << (bit))

#define OUTPORT		PORTA
#define IRQA		_BV(PORTA3)
#define IRQB		_BV(PORTA4)

#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>
#include <util/delay.h>

#include "ps2.h"
#include "lib/debug.h"
//#include "ps2_keymap.h"

#include "74xx164.h"
#include "config.h"

int main(void)
{

	//unsigned char c;
	
	init_dbug();
	init_PS2A();
	init_SR();
	sei();	

	for (;;) {
		// check the buffer for a scan code
		//c = ps2_buf_pull();
		//if (c != 0) {
			// Load the shift register
			//shiftOut(c);
			// raise interrupt
			//OUTPORT |= IRQA;
		//}
		//_delay_ms(100);
	}

	// TODO how to handle interrupt clear?
}

ISR (PS2A_PCINT_vect) {
	cli();
	set_dbug(2);
	static volatile uint8_t last = 0xFF; // default high because of pull up
	uint8_t changed;

	changed = PS2PIN ^ last;
	last = PS2PIN;

	if (changed & PS2A_CLK) {
		if((PS2PIN & PS2A_CLK) == 0) {
			ps2_read();
		}
	}
	clear_dbug(2);
	sei();
}
