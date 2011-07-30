all: tito.hex

#tito.hex: tito.c tito.h lib/lib_pwm.c lib/lib_pwm.h lib/lib_sensores.c lib/lib_sensores.h
tito.hex: tito.c tito.h
	avr-gcc -O -mmcu=atmega8 -Wall -o tito.bin -I/usr/avr/include/ tito.c 
	avr-objcopy -j .text -O ihex tito.bin tito.hex

program: tito.hex
	sudo avrdude -c usbtiny -p m8 -U f:w:tito.hex:i

clean:
	rm  *.bin *.hex
