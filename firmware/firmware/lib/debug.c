/*
 * debug.c
 *
 * Created: 3/31/2023 7:27:55 PM
 *  Author: Greg
 */ 

#include "debug.h"
#include "../config.h"

#define DBUG0	_BV(PORTB4)
#define DBUG1	_BV(PORTB5)
#define DBUG2	_BV(PORTB6)

void init_dbug() {
	DBUG_DDR |= DBUG0 | DBUG1 | DBUG2;
	DBUG_PORT &= ~DBUG0 & ~DBUG1 & ~DBUG2;
}

void set_dbug(uint8_t dbug) {
	switch(dbug) {
		case 0:
			DBUG_PORT |= DBUG0;
			break;
		case 1:
			DBUG_PORT |= DBUG1;
			break;
		case 2:
			DBUG_PORT |= DBUG2;
			break;
	}
}

void clear_dbug(uint8_t dbug) {
	switch(dbug) {
		case 0:
			DBUG_PORT &= ~DBUG0;
			break;
		case 1:
			DBUG_PORT &= ~DBUG1;
			break;
		case 2:
			DBUG_PORT &= ~DBUG2;
			break;
	}
}