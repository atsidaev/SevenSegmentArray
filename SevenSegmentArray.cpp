#include <avr/pgmspace.h>

#include "SevenSegmentArray.h"

const unsigned char ascii_maskp[] PROGMEM = 
{
  0x00, 0x86, 0x22, 0x7E, 0x7B, 0x63, 0x7E, 0x02,  /* !"#$%&'*/
  0x39, 0x0F, 0x63, 0x70, 0x80, 0x40, 0x80, 0x52,  /*()*+,-./*/
  0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07,  /*01234567*/
  0x7F, 0x6F, 0x00, 0x00, 0x58, 0x48, 0x4C, 0xA7,  /*89:;<=>?*/
  0x5C, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71, 0x3D,  /*@ABCDEFG*/
  0x76, 0x06, 0x1E, 0x72, 0x38, 0x55, 0x54, 0x3F,  /*HIJKLMNO*/
  0x73, 0x67, 0x50, 0x6D, 0x78, 0x3E, 0x1C, 0x1D,  /*PQRSTUVW*/
  0x49, 0x6E, 0x5b, 0x39, 0x64, 0x0F, 0x23, 0x08   /*XYZ[\]^_*/
};

SevenSegmentArray::SevenSegmentArray(INDICATOR_TYPE indicator_type, volatile uint8_t* digits_port, volatile uint8_t* segments_port, unsigned char* digits_pins, unsigned char digits_pins_count) {
	this->segments_port = segments_port;
	this->digits_port = digits_port;
	this->indicator_type = indicator_type;
	
	clear_digits_mask = 0;
	
	// DDRx is 1 lower that PORTx
	*(segments_port - 1) = 0xFF; // segment port has only outputs 
	volatile uint8_t* ddrx = digits_port - 1;
	uint8_t value = *ddrx;
	
	// collect mask data for digit selection pins
	for (int i = 0; i < digits_pins_count; i++)
	{
		uint8_t pin = 1 << digits_pins[i];
		value |= pin;
		clear_digits_mask |= pin;
		
		if (indicator_type == COMMON_CATHODE)
			pin ^= 0xFF;
			
		digit_masks[i] = pin;
	}
	
	// set digit pins as outputs
	*ddrx = value;
	
	if (indicator_type == COMMON_ANODE)
		clear_digits_mask = ~clear_digits_mask;
}

void SevenSegmentArray::select_digit(uint8_t digit) {
	// Turn off all digits, then turn on selected digit
	if (indicator_type == COMMON_CATHODE)
	{
		*digits_port |= clear_digits_mask;
		*digits_port &= digit_masks[digit];
	}
	else
	{
		*digits_port &= clear_digits_mask;
		*digits_port |= digit_masks[digit];
	}
}

void SevenSegmentArray::output_segments(char symbol) {
	// get symbol for the needed char code
	symbol = pgm_read_byte(&(ascii_maskp[symbol - ' ']));
	
	if (indicator_type == COMMON_CATHODE)
		*segments_port = symbol;
	else
		*segments_port = symbol ^ 0xFF;
}
