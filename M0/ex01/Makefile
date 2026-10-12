#Microcontroller model
MCU = atmega328p
#Processer frequency
F_CPU = 16000000UL
#Baud rate
BR = 115200
#Port to which attached MCU
PORT = /dev/ttyUSB0

#avr compiler and flags
CC = avr-gcc 
CF = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Wall -Wextra 
# -mmcu indicates which microcontroller to use

all: hex flash

hex: main.hex
	
main.hex: main.bin
	avr-objcopy -O ihex main.bin main.hex
#avr-objcopy extract and converts essential contents of an object file to raw data .hex

main.bin: main.c
	$(CC) $(CF) main.c -o main.bin

# flash = install code on mcu
flash: main.hex
	avrdude -c arduino -p $(MCU) -P $(PORT) -b $(BR) -U flash:w:main.hex

# avrdude Uploads compiled .hex files into mcu flash memory
# -c arduino: hardware programmer type
# -p: Specifies the mcu
# -P: communication port

# -U memtype:op:filename[:format] : Perform a memory operation
# memtype field specifies the memory type to operate on (flash in this case)
# w read the specified file and write it to the specified device memory

clean:
	rm -f main.hex main.bin 

.PHONY: hex flash clean all