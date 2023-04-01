/*
 * config.h
 *
 * Created: 3/31/2023 2:18:45 PM
 *  Author: Greg
 */

#include <avr/io.h> 

#define _BV(bit) (1 << (bit))

#ifndef CONFIG_H_
#define CONFIG_H_

#define PS2PORT		PORTB
#define PS2DDR		DDRB
#define PS2PIN		PINB
#define PS2A_CLK	_BV(PORTB0)
#define PS2A_DATA	_BV(PORTB1)
#define PS2B_CLK	_BV(PORTB2)
#define PS2B_DATA	_BV(PORTB3)

#define PS2A_PCIE	PCIE0
#define PS2A_PCINT	PCINT8
#define PS2A_PCINT_vect	PCINT_vect

#define PS2B_PCIE	PCIE0
#define PS2B_PCINT	PCINT10
#define PS2B_PCINT_vect	PCINT_vect

#define SR_PORT		PORTA
#define SR_DDR		DDRA
#define SR_CS		_BV(PORTA0)
#define SR_DATA		_BV(PORTA1)
#define SR_CLK		_BV(PORTA2)

#define DBUG_PORT	PORTB
#define DBUG_DDR	DDRB

#endif /* CONFIG_H_ */