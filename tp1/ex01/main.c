#include <avr/io.h>

int main()
{
   //set toutes les pin B en input
   DDRB = (1 << PB1);
   //set com1B1 et com1B0 COM1A0
   ICR1 = 31249;
   OCR1A = 3124;
   TCCR1A |= (1 << COM1A1);
   TCCR1A |= (1 << COM1B1);
   //TCCR1A = (1 << COM1A1);
   //TCCR1A = (1 << WGM10);
   //mode 14
   TCCR1A |= (1 << WGM11);
   TCCR1B |= (1 << WGM12);
   TCCR1B |= (1 << WGM13);

   //set clock timer a 1024
   TCCR1B |= (1 << CS12);
   TCCR1B |= (1 << CS10);
   //garder le programme en vie
   while(1)
   {

   }
}
