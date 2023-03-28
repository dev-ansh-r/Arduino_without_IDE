#include <avr/io.h>
#include <util/delay.h>

int main(void){

DDRB |= (1 << PB5); //set pin 13 as an output, refer schematic diagram for avr atmel 328p for port informations
while(1){
PORTB ^= (1 << PB5); //toggle pin 13
_delay_ms(500);
}
return 0;
}
