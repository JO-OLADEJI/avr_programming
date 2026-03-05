MCU = atmega328p
CC = avr-gcc
CC_HEX = avr-objcopy
CC_FLAGS = -mmcu=$(MCU) -Os
AVRDUDE = avrdude

clean:
	rm -f *.out *.elf *.hex
	echo "cleaned compiled files. Thank you"

build:
	$(CC) $(CC_FLAGS) -o serial.elf serial.c
	$(CC_HEX) -O ihex serial.elf serial.hex

flash:
	$(AVRDUDE) -c usbasp -p m328pb -U flash:w:serial.hex
