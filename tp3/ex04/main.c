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


char uart_rx(void){
   //waiting reception
  while(!(UCSR0A & (1 << RXC0)));
   return(UDR0);
}

/*int str_cmp(char *a, char *b){
   int i = 0;
   while(a[i] && b[i] && a[i] == b[i]){
      i++;
   }
   uart_tx('[');
   uart_tx(a[i]);
   uart_tx(b[i]);
uart_tx(']');

   return((unsigned char)b[i] - (unsigned char)a[i]);
}*/


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
         else if(login[i] == 127 && i != 0){
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
         else if(password[i] == 127 && i != 0){
            i--;
            password[i] = '\0';
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
      char *a = "huggo";
      char *b = "123";
      while(login[i] && a[i] && login[i] == a[i]){
         i++;
      }
      i = 0;
      while(password[i] && b[i] && password[i] == b[i]){
         i++;
      }

      if(login[i] - a[i] || password[i] - b[i]){ //la commande voule est if(str_cmp(login, "huggo") || str_cmp(login, "123"))
         uart_printstr("\n\rMauvaise combinaison username/password\n\n\n\r");
      }
      else{
         uart_printstr("\n\rCOUCOU ");
         uart_printstr(login);
         uart_printstr("!!!!!!!!!!!!!!!!");
         while(1){
            PORTB = PORTB << 1;
        long x = 0;
        while(x < 200000)
            x++;
        PORTB = PORTB >> 1;
        x = 0;
        while(x < 200000)
            x++;
         }
      }
      i = 0;
   }
}