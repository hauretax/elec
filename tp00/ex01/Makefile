all : hex flash

hex :
	avr-gcc -std=c99 -Wall -ffunction-sections -I. -mmcu=atmega328p -DF_CPU=16000000UL -o main.bin main.c
	avr-objcopy -j .text -j .data -O ihex main.bin main.hex

flash : 
	avrdude -p atmega328p -c arduino -P /dev/tty.SLAB_USBtoUART -b 115200  -D -U flash:w:main.hex
