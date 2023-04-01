#include <avr/io.h>
#include <util/atomic.h>
#include <inttypes.h>

#include "ps2.h"
#include "lib/debug.h"
#include "config.h"

#define PS2_BUF_LEN 128U

//static void _decode(unsigned char);

unsigned char _buf[PS2_BUF_LEN];
uint8_t _bufBegin = 0;
uint8_t _bufEnd = 0;

//extern unsigned char _unshifted[67][2];
//extern unsigned char _shifted[67][2];

void init_PS2A() {
	PS2DDR &= ~PS2A_CLK;	// Set PS2A clock as input
	PS2DDR &= ~PS2A_DATA;	// Set PS2A data as input
	PS2PORT |= PS2A_CLK;	// Pull up PS2A clock pin
	PS2PORT |= PS2A_DATA;	// Pull up PS2A data pin
	GIMSK &= PS2A_PCIE;		// Enable pin change interrupts
	PCMSK1 &= PS2A_PCINT;	// Enable pin change interrupt for PS2A clock pin
}

void ps2_read() {
	static unsigned char data;
	static unsigned char bitcount = 11;
	
	set_dbug(0);

	if ((bitcount < 11) && (bitcount > 2)) {
		data = (data >> 1);
		if (PS2PIN & PS2A_DATA) {
			data = data | 0x80; // store 1
		} else {
			data = data & 0x7f; // store 0
		}
	}

	if (--bitcount == 0) {
		//_decode(data);
		ps2_buf_push(data);
		bitcount = 11;
	}
	clear_dbug(0);
}

void ps2_buf_push(unsigned char c)
{
	set_dbug(1);
	ATOMIC_BLOCK(ATOMIC_FORCEON) {
		_buf[_bufEnd] = c;
		if (_bufEnd + 1 == PS2_BUF_LEN) {
			_bufEnd = 0;
		} else {
			_bufEnd++;
		}

		if (_bufEnd == _bufBegin) {
			if (_bufBegin + 1 == PS2_BUF_LEN) {
				_bufBegin = 0;
			} else {
				_bufBegin++;
			}
		}
	}
	clear_dbug(1);
}

unsigned char ps2_buf_pull(void) {
	unsigned char c;
	ATOMIC_BLOCK(ATOMIC_FORCEON) {
		if (_bufBegin == _bufEnd)
			return 0;
		c = _buf[_bufBegin];
		if (_bufBegin + 1 == PS2_BUF_LEN) {
			_bufBegin = 0;
		} else {
			_bufBegin++;
		}
	}
	return c;
}

void ps2_buf_empty(void) {
	_bufBegin = 0;
	_bufEnd = 0;
}

//static void _decode(unsigned char scan_code) {
	//static unsigned char is_up = 0;
	//static unsigned char shift = 0;
	//unsigned char i;
//
	//if (!is_up) {
		//switch(scan_code) {
			//case 0xF0: //Up key
				//is_up = 1;
				//break;
			//case 0x12: //left shift
			//case 0x59: //right shift
				//shift = 1;
				//break;
			//default:
				//if (!shift) {
					//for (i = 0; _unshifted[i][0] != scan_code && _unshifted[i][0]; i++);
					//if (_unshifted[i][0] == scan_code) {
						//ps2_buf_push(_unshifted[i][1]);
					//}
				//} else {
					//for (i = 0; _shifted[i][0] != scan_code && _shifted[i][0]; i++);
					//if (_shifted[i][0] == scan_code) {
						//ps2_buf_push(_shifted[i][1]);
					//}
				//}
				//break;
		//}	
	//} else {
		//is_up = 0;
		//switch(scan_code) {
			//case 0x12: //left shift
			//case 0x59: //right shift
				//shift = 0;
				//break;
		//}
	//}
//}