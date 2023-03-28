MCU = atmega328p
F_CPU = 16000000UL
PROGRAMMER = arduino
PORT = /dev/ttyACM0

CC = avr-gcc
CFLAGS = -Wall -Os -DF_CPU=$(F_CPU) -mmcu=$(MCU)

OBJCOPY = avr-objcopy
OBJCOPYFLAGS = -j .text -j .data -O ihex

AVRDUDE = avrdude
AVRDUDEFLAGS = -p $(MCU) -c $(PROGRAMMER) -P $(PORT)

all: blink.hex

blink.hex: blink.elf
	$(OBJCOPY) $(OBJCOPYFLAGS) $< $@

blink.elf: blink.o
	$(CC) $(CFLAGS) -o $@ $<

blink.o: blink.c
	$(CC) $(CFLAGS) -c $<

upload: blink.hex
	$(AVRDUDE) $(AVRDUDEFLAGS) -U flash:w:$<

clean:
	rm -f blink.o blink.elf blink.hex
