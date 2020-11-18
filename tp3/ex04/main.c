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
   //set bit size to 8 
   UCSR0C = (1<<UCSZ00);
   UCSR0C |= (1<<UCSZ01);
}

void uart_tx(char c){
   while(!(UCSR0A & (1 << UDRE0)));
   if(UDR0 == '\r'){//c est ligne son techniquement inutile mais sa boucle sans
      UDR0 = '\n';
      while(!(UCSR0A & (1 << UDRE0)));
   }
   UDR0 = c;   
}

void uart_printstr(char *str){
   int i = 0;

   while (str[i]){
      uart_tx(str[i]);
      i++;
   }    
}
/*
interrupt_handler(USART_RX_vect){ 
   while(!(UCSR0A & (1 << RXC0)));
   uart_tx('q');
     // uart_printstr("abcd");
}*/

char uart_rx(void){
   //waiting reception
  while(!(UCSR0A & (1 << RXC0)));
   return(UDR0);
}

int str_cmp(char *a, char *b){
   int i = 0;
   while(a[i] && b[i] && (a[i] == b[i])){
      i++;
   }
   return(a[i] != b[i]);
}

int main()
{  
   char login[7] = {'\0','\0','\0','\0','\0','\0','\0'};
   char password[5]={'\0','\0','\0','\0','\0'};
   int i = 0;
   DDRB |= (1 << PB1);
   DDRB |= (1 << PB2);
   DDRB |= (1 << PB3);
   DDRB |= (1 << PB0);

   uart_init(MYUBRR);
   while(1){
         uart_printstr("Bonjour ! Entrez votre login:\r\n    username: ");
      while (i < 6){
         login[i] = uart_rx();
         if(login[i] == '\r'){
            login[i] = '\0';
             break ;
         }
         if(login[i] == 127 && i != 0){
            i--;
            login[i] = '\0';
            uart_tx(8);
            uart_tx(' ');
            uart_tx(8);
         }
         else{
            uart_tx(login[i]);
            i++;
         }
      }
      i = 0;
      uart_printstr("\r\n    password: ");
      while (i < 4){
         password[i] = uart_rx();
         if(password[i] == '\r'){
            password[i] = '\0';
             break ;
         }
         if(login[i] == 127 && i != 0){
            i--;
            login[i] = '\0';
            uart_tx(8);
            uart_tx(' ');
            uart_tx(8);
         }
         else{
            uart_tx('*');
            i++;
         }
      }
      i = 0;
      if(str_cmp(login, "huggo") && str_cmp(password, "123"))
         uart_printstr("\n\rMauvaise combinaison username/password\n\n\n\r");
      else{
         uart_printstr("\n\rCOUCOU ");
         uart_printstr(login);
         uart_printstr("!!!!!!!!!!!!!!!!");
         PORTB = 0b1000;
         while(1){
         if (PORTB == 0b1111)
            PORTB = 0b1000;
         for(int x = 0;x < 1000; x++)
            ;
            PORTB >>=1;
         }
      }
   }
}