all: tito.hex

#tito.hex: tito.c tito.h lib/lib_pwm.c lib/lib_pwm.h lib/lib_sensores.c lib/lib_sensores.h
tito.hex: tito.c tito.h lib/lib_pwm.c lib/lib_pwm.h 
	avr-gcc -O -mmcu=atmega8 -Wall -o tito.bin -I/usr/avr/include/ tito.c lib/lib_pwm.c
	avr-objcopy -j .text -O ihex tito.bin tito.hex

program: tito.hex
	sudo avrdude -c usbtiny -p m8 -F -U f:w:tito.hex:i

program_ns: tito.hex
	avrdude -c usbtiny -p m8 -F -U f:w:tito.hex:i
	
tito_punteros_prueba.hex: tito_punteros_prueba.c tito.h lib/lib_pwm.c lib/lib_pwm.h 
	avr-gcc -O -mmcu=atmega8 -Wall -o tito_punteros_prueba.bin -I/usr/avr/include/ tito_punteros_prueba.c lib/lib_pwm.c
	avr-objcopy -j .text -O ihex tito_punteros_prueba.bin tito_punteros_prueba.hex

program_prueba: tito_punteros_prueba.hex
	sudo avrdude -c usbtiny -p m8 -F -U f:w:tito_punteros_prueba.hex:i

program_prueba_ns: tito_punteros_prueba.hex
	avrdude -c usbtiny -p m8 -F -U f:w:tito_punteros_prueba.hex:i

tito_estable.hex: tito_estable.c tito_estable.h lib/lib_pwm.c lib/lib_pwm.h 
	avr-gcc -O -mmcu=atmega8 -Wall -o tito_estable.bin -I/usr/avr/include/ tito_estable.c lib/lib_pwm.c
	avr-objcopy -j .text -O ihex tito_estable.bin tito_estable.hex

program_estable: tito_estable.hex
	sudo avrdude -c usbtiny -p m8 -F -U f:w:tito_estable.hex:i

program_estable_ns: tito_estable.hex
	avrdude -c usbtiny -p m8 -F -U f:w:tito_estable.hex:i
	
clean:
	rm  *.bin *.hex
