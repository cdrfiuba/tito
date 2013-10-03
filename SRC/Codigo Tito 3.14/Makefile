CLK = 1000000UL
MMCU = atmega88

all: clean tito.hex size

tito.hex: tito.c tito.h lib/motores.c lib/motores.h velocidades.h lib/common.h
	avr-gcc -Os -mcall-prologues -mmcu=$(MMCU) -Wall -DF_CPU=$(CLK) -o tito.bin -I/usr/avr/include/ tito.c lib/motores.c
	avr-objdump -h -S tito.bin > tito.lst
	avr-objcopy -j .text -j .data -O ihex tito.bin tito.hex

program_su: clean tito.hex size
	sudo avrdude -c usbtiny -p m88 -F -U f:w:tito.hex:i

program: clean tito.hex size
	avrdude -c usbtiny -p m88 -F -U f:w:tito.hex:i
	
clean:
	rm -rf *.bin *.hex *.lst
	
size:	
	avr-size -d --format=avr --mcu=$(MMCU) tito.bin
	avr-size tito.bin

