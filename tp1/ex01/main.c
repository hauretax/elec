#include <avr/io.h>

int main()
{
   //set toutes les pin B en output
   DDRB = (1 << PB1);
   //set Icr1 pour faire des boucle de 1sec
   ICR1 = 62499;
   //set ocr1a pour etre allmuer 10% du temps de boucle
   OCR1A = 6249;
   //set TCCR1A sur clear on compare match (en fast pwm)
   TCCR1A |= (1 << COM1A1);
   //TCCR1A = (1 << COM1A1);
   //TCCR1A = (1 << WGM10);
   //set le mode 14
   TCCR1A |= (1 << WGM11);
   TCCR1B |= (1 << WGM12);
   TCCR1B |= (1 << WGM13);

   //set clock timer a 256
   TCCR1B |= (1 << CS12);
   //TCCR1B |= (1 << CS10);
   //garder le programme en vie
   while(1)
   {

   }
   //pour plus d info :
}
