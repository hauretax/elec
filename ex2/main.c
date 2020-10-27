#include <avr/io.h>

int main(void){
    //autorise l'output pour le port pb3
    DDRB= (1 << PB3);
    while (1){
        //allume la led pb3
        PORTB= 0b00001000;
    }
    return (0); 
}