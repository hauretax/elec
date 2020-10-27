#include <avr/io.h>



int main(void){
    //autorise l'output pour le port pb3
    DDRB= 0xFF;
    PORTB= 0b00001000;
    int i = 1;
    int y = 0;

    while (1){
       if(!(PIND & (1 << PD3)))
        {
            y++;
            while(!(PIND & (1 << PD3)))
                ;
        }
        for(int x = 0; x < 1000; x++)
            ;
    }
    return (0); 
}