#include <avr/io.h>

#define  interrupt_handler(vector) \
         void vector (void) __attribute__ ((signal)) __VA_ARGS__; \
         void vector (void)

interrupt_handler(INT1_vect){
   PORTB = 0b1111;
}

int main()
{
   //set toutes les pin B en output
   DDRB |= (1 << PB1);
   DDRB |= (1 << PB2);
   DDRB |= (1 << PB3);
   DDRB |= (1 << PB0);
   //1 set maske 
   EIMSK = (1 << INT1);
   //2 activer linterupte!!!!!
   SREG = 0b10000000;

   while(1)
   {
   }
   //pour plus d info :
}
