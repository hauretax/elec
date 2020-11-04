#include <avr/io.h>



int main(void){
    //autorise l'output pour le port pb3
    DDRB= (1 << PB3);
    PORTB= 0b00001000;
    int i = 1;

    while (1){
       if(!(PIND & (1 << PD3)))
        {
            if(i == 0)
            {
                PORTB= 0b00001000;
                i = 1;
            }
            else{
                PORTB= 0b00000000;
                i = 0;
            }
            while(!(PIND & (1 << PD3)))
                ;
       
        for(int x = 0; x < 10000; x++)
            ;
	}
    }
    return (0); 
}
