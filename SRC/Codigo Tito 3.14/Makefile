CLK = 8000000UL
MMCU = atmega88
TARGET_P = m88
# default hfuse
HFUSE = 0xdf
# internal clock, no divide by 8
LFUSE = 0xf2


all: clean tito.hex

tito.hex: tito.c tito.h lib/motores.c lib/motores.h velocidades.h lib/common.h
	avr-gcc -O3 -mmcu=$(MMCU) -Wall -DF_CPU=$(CLK) -o tito.bin -I/usr/avr/include/ tito.c lib/motores.c
#	avr-gcc -O3 -mmcu=$(MMCU) -Wall -Wl,-u,vfprintf -lprintf_min -DF_CPU=$(CLK) -o tito.bin -I/usr/avr/include/ tito.c lib/motores.c
	avr-objdump -h -S tito.bin > tito.lst
	avr-objcopy -j .text -j .data -O ihex tito.bin tito.hex

program_su: clean tito.hex size
	sudo avrdude -c usbtiny -p $(TARGET_P) -F -U f:w:tito.hex:i

program: clean tito.hex
	avrdude -c usbtiny -p $(TARGET_P) -F -U f:w:tito.hex:i
	
clean:
	rm -rf *.bin *.hex *.lst
	
size:	
	avr-size -d --format=avr --mcu=$(MMCU) tito.bin
	avr-size tito.bin

fuse:
	avrdude -c usbtiny -p $(TARGET_P) -U lfuse:w:$(LFUSE):m -U hfuse:w:$(HFUSE):m

