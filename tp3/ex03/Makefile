USB = /dev/ttyUSB0
FREQUANCE = -DF_CPU=16000000UL
FLAG = -Wall

all : hex flash clear

hex :
	avr-gcc -std=c99 $(FLAG) -ffunction-sections -I. -mmcu=atmega328p $(FREQUANCE) -o main.bin main.c
	avr-objcopy -j .text -j .data -O ihex main.bin main.hex

flash : 
	avrdude -p atmega328p -c arduino -P $(USB) -b 115200  -D -U flash:w:main.hex

clear :
	rm main.bin main.hex