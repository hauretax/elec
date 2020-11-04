#include <avr/io.h>

int main()
{
   //set toutes les pin B en input
   DDRB = 0xFF;
   //set com1B1 et com1B0 COM1A0
   OCR1A = 62499;
   TCCR1A = (1 << COM1A0);

   //mode 4
   //TCCR1A = (1 << COM1A1);
   //TCCR1A = (1 << WGM10);
   //TCCR1A = (1 << WGM11);
   TCCR1B = (1 << WGM12);

   //TCCR1B = (1 << WGM13);
   //set clock timer a 256
   TCCR1B |= (1 << CS12);
   //garder le programme en vie
   while(1)
   {

   }
}
