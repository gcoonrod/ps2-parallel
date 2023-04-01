/*
 * _74xx164.c
 *
 * Created: 3/31/2023 2:00:06 PM
 *  Author: Greg
 */ 

//#define F_CPU 8000000UL  // 8.0 MHz

//#include <util/delay.h>

#include "74xx164.h"
#include "config.h"

void init_SR() {
	// Configure outputs
	SR_DDR |= SR_CS;
	SR_DDR |= SR_DATA;
	SR_DDR |= SR_CLK;

	// Initialize outputs
	SR_PORT &= ~SR_CS;
	SR_PORT |= SR_CLK;
	SR_PORT &= ~SR_DATA;
}

void shiftOut(unsigned char c) {
	SR_PORT |= SR_CS; // Set "chip select" high
	for (uint8_t i = 0; i < 8; i++) {
		if (c & _BV(i)) {
			SR_PORT |= SR_DATA; // write 1
		} else {
			SR_PORT &= ~SR_DATA; // write 0
		}

		// Pulse the clock
		SR_PORT &= ~SR_CLK;
		SR_PORT |= SR_CLK;
	}
	SR_PORT &= ~SR_CS; 
}
