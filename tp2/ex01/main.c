#include <avr/io.h>

#define  interrupt_handler(vector, ...) \
         void vector (void) __attribute__ ((signal)) __VA_ARGS__; \
         void vector (void)



interrupt_handler(TIMER0_COMPA_vect){  
   static int i = 1;  
   if(ICR1 == OCR1A)
      i = 0;
   if(!(OCR1A))
      i = 1;
   if(i){
         OCR1A ++;
   }
   else{
         OCR1A--;
   }
}

int main()
{
   //set toutes les pin B en output
   DDRB |= (1 << PB1);
   DDRB |= (1 << PB2);
   DDRB |= (1 << PB3);
   DDRB |= (1 << PB0);


   ICR1 = 125;
   //set ocr1a pour etre allmuer 10% du temps de boucle
   OCR1A=0;
   //set TCCR1A sur clear on compare match (en fast pwm)
   TCCR1A |= (1 << COM1A1);
   //TCCR1A = (1 << COM1A1);
   //TCCR1A = (1 << WGM10);
   //set le mode 14
   TCCR1A |= (1 << WGM11);
   TCCR1B |= (1 << WGM12);
   TCCR1B |= (1 << WGM13);
   //set le presclaer
   //TCCR1B |= (1 << CS12);
   TCCR1B |= (1 << CS10);

   //set toggle
   TCCR0A |= (1 << COM0B0);
   //set le mode 2
   TCCR0A |= (1 << WGM01);
   TCCR0A |= (1 << WGM00);
   TCCR0B |= (1 << WGM02);
   //set maske 
   TIMSK0 |= (1 << INT1);
   //activer linterupte!!!!!
   SREG |= 0b10000000;
   //set le max
   OCR0A = 255;
   //set clock timer a 1024
   TCCR0B |= (1 << CS02);
   TCCR0B |= (1 << CS00);
   while(1)
   {
   }
   //pour plus d info :
}
