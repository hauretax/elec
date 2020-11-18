#include <avr/io.h>
#define MYUBRR 16000000/8/115000-1

#define  interrupt_handler(vector) \
         void vector (void) __attribute__ ((signal)); \
         void vector (void)

/* T!!! ==== TRANSMITE */
/* R!!! ==== RECEIVED  */

void uart_init(unsigned int ubrr)
{
   //double speed operation
   UCSR0A = (1<<U2X0);
   //load my beauty ubrr on bot and top i suposd ???
   UBRR0H = (unsigned char) (ubrr>>8);
   UBRR0L = (unsigned char) ubrr;
   //set on on tx and rx and interupt on rx
   UCSR0B = (1<<RXEN0) | (1<<TXEN0) ;
   UCSR0B |= (1<<RXCIE0);
   //set bit size to 8 
   UCSR0C = (1<<UCSZ00);
   UCSR0C |= (1<<UCSZ01);
}

void uart_tx(char c){
   while(!(UCSR0A & (1 << UDRE0)));
      if(UDR0 == '\r'){
         UDR0 = '\n';
         while(!(UCSR0A & (1 << UDRE0)));
      }
   UDR0 = c;
}

interrupt_handler(USART_RX_vect){ 
   while(!(UCSR0A & (1 << RXC0)));
   char q = UDR0;  //je rajoute une variable pour ne rien comparer as UDR0
   if(q >= 'A' && q <= 'Z')
      uart_tx(q + 32);
   else if(q >= 'a' && q <= 'z') //fait des bugs quand je compare as UDR0
      uart_tx(q - 32);
   else
      uart_tx(q);
}

int main()
{  
   uart_init(MYUBRR);
      //active l interuption global!
   SREG |= (1 << SREG_I);
    while(1)
    {
    }
}