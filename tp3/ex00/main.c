#include <avr/io.h>
#define MYUBRR 16000000/8/115000-1

#define  interrupt_handler(vector, ...) \
         void vector (void) __attribute__ ((signal)) __VA_ARGS__; \
         void vector (void)

interrupt_handler(TIMER0_COMPA_vect){  

}

void uart_init(unsigned int ubrr)
{
   //set buffer to send
   UCSR0A = (1<<U2X0);
   UBRR0H = (unsigned char) (ubrr>>8);
   UBRR0L = (unsigned char) ubrr;
   UCSR0B = (1<<RXEN0) | (1<<TXEN0);
   UCSR0C = (1<<UCSZ00);
   UCSR0C |= (1<<UCSZ01);
}

void uart_tx(){
   UDR0 = 'z';
}

int main()
{  
   uart_init(MYUBRR);
    while(1)
    {
      for(int x = 0; x<1600000; x++){
         ;
         }
         uart_tx();
    }
}