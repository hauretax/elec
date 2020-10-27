#include <avr/io.h>

int addOne(int x) 
{
    PORTB = 0b00000000;
    int m = 1; 
      

    while( x & m ) 
    { 
        x = x ^ m;
        m <<= 1;
    }
    x = x ^ m; 

    if(x & 0b1000)
        PORTB |= 0b00001000;
    if(x & 0b0100)
        PORTB |= 0b00000100;
    if(x & 0b0010)
        PORTB |= 0b00000010;
    if(x & 0b0001)
        PORTB |= 0b00000001;
    return x; 
} 

int main(void){
    //autorise l'output pour le port pb3
    DDRB= 0xFF;
    PORTB= 0b00000000;
    int i = 0;

    while (1){
       if(!(PIND & (1 << PD3)))
        {
           i = addOne(i);
            while(!(PIND & (1 << PD3)))
                ;
        }
        for(int x = 0; x < 1000; x++)
            ;
    }
    return (0); 
}