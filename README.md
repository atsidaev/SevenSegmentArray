# SevenSegmentArray
AVR Library for handling 7-segment displays

There are several libraries for AVR/Arduino for working with 7-segment indicators. 
But none of them can handle more than one display connected in parallel.
SevenSegmentArray is a library intended to handle any number of indicators.

## Connection
**a**, **b**, **c**, **d**, **e**, **f**, **g** and **dot** of all displays should be connected together and attached to one of AVR ports.
**a** should be bit 0, **b** should be bit 1 and so on.

## Example
Let we have 3-digit 7-segment indicator with common cathode. **digit** pins are connected to *D1*, *D2* and *D3*; segment pins are connected to *PORTB*.

```
#include <avr/io.h>
#include <util/delay.h>

#include "SevenSegmentArray.h"

unsigned char digits[] = { 1, 2, 3 }; // 
SevenSegmentArray display(COMMON_CATHODE, &PORTD, &PORTB, digits, 3);

int main() {
  char buf[] = "HEY";
  while (1)
  {
    for (int i = 0; i < 3; i++)
    {
      display.select_digit(i);
      display.output_segments(buf[i]);
      _delay_ms(1);
    }
  }
}

```
