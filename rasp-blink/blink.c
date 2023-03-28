#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
  DDRB |= (1 << PB5); // Set pin 13 as an output
  while (1) {
    PORTB ^= (1 << PB5); // Toggle pin 13
    _delay_ms(500);
  }
  return 0;
}
