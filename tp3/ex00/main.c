#include <avr/io.h>
#define MYUBRR 16000000/8/115000-1

#define  interrupt_handler(vector) \
         void vector (void) __attribute__ ((signal)); \
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

void uart_tx(char c){
    while(!(UCSR0A & (1 << UDRE0)));
   UDR0 = c;
}

interrupt_handler(TIMER1_COMPA_vect){
   uart_tx('z');
}

int main()
{  
   //set clear on togll match
   TCCR1A |= (1 << COM1A0);
   //set le mode 4
   TCCR1A |= (1 << WGM12);
   //TCCR1A |= (1 << WGM13);
   //compare A match is enabled
   TIMSK1 |= (1 << OCIE1A);
   TIFR1 |= (1 << OCF1A);
   //active l interupte!
   SREG |= (1 << SREG_I);
   //set le top
   OCR1A = 25;
   //set prescaling to 256
   TCCR1B |= (1 << CS12);

   uart_init(MYUBRR);
    while(1)
    {

    }
}