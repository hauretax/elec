#include <avr/io.h>

int main(void){
    //autorise l'output pour le port pb3
    DDRB= (1 << PB3);
    PORTB= 0b00001000;
    while (1){
        //allume la led pb3        
        PORTB = PORTB << 1;
        long i = 0;
        while(i < 200000)
            i++;
        //eteint la led
        PORTB = PORTB >> 1;
        i = 0;
        while(i < 200000)
            i++;
    }
    return (0); 
}
