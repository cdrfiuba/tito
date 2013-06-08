CLK = 8000000UL
MMCU = atmega88

all: tito.hex

tito.hex: tito.c tito.h lib/lib_pwm.c lib/lib_pwm.h velocidades.h
	avr-gcc -Os -mcall-prologues -mmcu=$(MMCU) -Wall -DF_CPU=$(CLK) -o tito.bin -I/usr/avr/include/ tito.c lib/lib_pwm.c
	avr-objcopy -j .text -j .data -O ihex tito.bin tito.hex
	avr-size -d --format=avr --mcu=$(MMCU) tito.bin
	avr-size tito.bin

program_su: tito.hex
	sudo avrdude -c usbtiny -p m88 -F -U f:w:tito.hex:i

program: tito.hex
	avrdude -c usbtiny -p m88 -F -U f:w:tito.hex:i
	
clean:
	rm -rf *.bin *.hex
