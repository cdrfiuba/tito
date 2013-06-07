all: tito.hex

tito.hex: tito.c tito.h lib/lib_pwm.c lib/lib_pwm.h velocidades.h
	avr-gcc -Os -mcall-prologues -mmcu=atmega88 -Wall -o tito.bin -I/usr/avr/include/ tito.c lib/lib_pwm.c
	avr-objcopy -j .text -O ihex tito.bin tito.hex

program: tito.hex
	sudo avrdude -c usbtiny -p m88 -F -U f:w:tito.hex:i

program_ns: tito.hex
	avrdude -c usbtiny -p m88 -F -U f:w:tito.hex:i
	
clean:
	rm  *.bin *.hex
