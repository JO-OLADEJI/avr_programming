MCU = atmega328p
CC = avr-gcc
CC_HEX = avr-objcopy
CC_FLAGS = -mmcu=$(MCU) -Os
AVRDUDE = avrdude

FILE ?= io

clean:
	rm -f *.out *.elf *.hex
	echo "cleaned compiled files. Thank you"

build:
	$(CC) $(CC_FLAGS) -o $(FILE).elf $(FILE).c
	$(CC_HEX) -O ihex $(FILE).elf $(FILE).hex

flash:
	$(AVRDUDE) -c usbasp -p m328pb -U flash:w:$(FILE).hex
