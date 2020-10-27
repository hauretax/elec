NAME = main.bin
CC = avr-gcc
SRC = main.c
F_CPU = -DF_CPU=16000000UL
FLAG = -Wall
all : hex flash


hex :
$(CC) -std=c99 $(FLAG) -ffunction-section -I. -mmcu=atmega328p &(F_CPU)  $(SRC) -o $(NAME)
avr-objcopy -j .text -j .data -O ihex main.bin main.hex

flash : 
avrdude -p atmega328p -c arduino -P /dev/tty. -b 115200  -D -U flash:w:main.hex:i

