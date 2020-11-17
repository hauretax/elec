#include <avr/io.h>
#define MYUBRR 16000000/8/115000-1

#define  interrupt_handler(vector) \
         void vector (void) __attribute__ ((signal)); \
         void vector (void)


void uart_init(unsigned int ubrr)
{
  ///mode u2x0
   UCSR0A = (1<<U2X0);
   UBRR0H = (unsigned char) (ubrr>>8);
   UBRR0L = (unsigned char) ubrr;
   UCSR0B = (1<<RXEN0) | (1<<TXEN0);
   UCSR0C = (1<<UCSZ00);
   UCSR0C |= (1<<UCSZ01);
}

void uart_tx(){
    //set buffer to send
   UDR0 = 'z';
}
interrupt_handler(TIMER1_COMPA_vect){  
   uart_tx();
   PORTB = 0b1111;
   for(int x = 0; x < 1000; x++)
      ;
}

int main()
{  
   DDRB |= (1 << PB1);
   //set toggle
   TCCR1A |= (1 << COM1B0);
   TCCR1A |= (1 << COM1A0);
   //set le mode 4 ctc
   TCCR0A |= (1 << WGM12);
   //enabled timer captur on timer1
   TIMSK1 |= (1 << ICIE1);
   //activer linterupte!!!!!
   SREG |= (1 << SREG_I);
   //set le max
   OCR1A = 255;
   //set clock timer a 256
   TCCR1B |= (1 << CS12);

   uart_init(MYUBRR);
    while(1)
    {
       PORTB = 0b0;
    }
}