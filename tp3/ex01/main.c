#include <avr/io.h>
#define MYUBRR 16000000/8/115000-1
/*
#define  interrupt_handler(vector, ...) \
         void vector (void) __attribute__ ((signal)) __VA_ARGS__; \
         void vector (void)

interrupt_handler(TIMER0_COMPA_vect){  

}
*/
void uart_init(unsigned int ubrr)
{
   //double speed operation
   UCSR0A = (1<<U2X0);
   //load my beauty ubrr on bot and top i suposd ???
   UBRR0H = (unsigned char) (ubrr>>8);
   UBRR0L = (unsigned char) ubrr;
   //set on on tx and rx
   UCSR0B = (1<<RXEN0) | (1<<TXEN0);
   //set bit size to 8 
   UCSR0C = (1<<UCSZ00);
   UCSR0C |= (1<<UCSZ01);
}

void uart_tx(char c){
   UDR0 = c;
}

void uart_printstr(char *str){
   int i = 0;

   while (str[i]){
      while(!(UCSR0A & (1<<UDRE0)))
         ;
      uart_tx(str[i]);
      i++;
   }
      
}

int main()
{  
   uart_init(MYUBRR);
    while(1)
    {
         uart_printstr("Hello World!\n\r");
      for(int x = 0; x<30000; x++){
         for(int w = 0; w< 56; w++)
               ;
            ;
         }
    }
}