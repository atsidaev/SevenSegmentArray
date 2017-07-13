#ifndef SEVEN_SEGMENT_ARRAY_H
#define SEVEN_SEGMENT_ARRAY_H

#include <stdint.h>

enum INDICATOR_TYPE { COMMON_CATHODE, COMMON_ANODE };
#define DIGITS_COUNT 4

class SevenSegmentArray {
	private:
		uint8_t digit_masks[8];
		uint8_t clear_digits_mask;
		
		INDICATOR_TYPE indicator_type;
		volatile uint8_t* segments_port;
		volatile uint8_t* digits_port;
	
	public:
		SevenSegmentArray(INDICATOR_TYPE indicator_type, volatile uint8_t* digits_port, volatile uint8_t* segments_port, unsigned char* digits_pins, unsigned char digits_pins_count);
		void select_digit(uint8_t digit);
		void output_segments(char symbol);
};

#endif
