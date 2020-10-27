#include <avr/io.h>



int main(void){
    //autorise l'output pour le port pb3
    DDRB= (1 << PB3);
    
    while (1){
       if(PIND & (1 << PD3))
        PORTB= 0b00000000;
       else
        PORTB= 0b00001000;
    }
    return (0); 
}