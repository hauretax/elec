NAME = main.bin
CC = avr-gcc
SRC = main.c
F_CPU = 16000000

all : hex flash

hex :
$(CC)  $(SRC) -o $(NAME)

flash : 
avrdude

