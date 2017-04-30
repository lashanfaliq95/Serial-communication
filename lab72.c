#include "avr/io.h"

void usart_init(){
  // Enabling receiving and transmitting
  UCSR0B |= (1<<RXEN0);
  UCSR0B |= (1<<TXEN0);

  // Setting to Asynchronous mode
  UCSR0C &= ~(1<<UMSEL01);
  UCSR0C &= ~(1<<UMSEL00);

  // Setting to 8-bit data frame
  UCSR0C &= ~(1<<UCSZ02);
  UCSR0C |= (1<<UCSZ01);
  UCSR0C |= (1<<UCSZ00);

  // Setting to no parity
  UCSR0C &= ~(1<<UPM01);
  UCSR0C &= ~(1<<UPM00);

  // Setting to one stop bit
  UCSR0C &= ~(1<<USBS0);

  // Setting baudrate to 9600bps
  UBRR0 = 103;

}

void usart_send(unsigned char data){
  // Wait till UDR0 is ready
  while (!(UCSR0A & (1<<UDRE0)));

  // Put data into buffer
  UDR0 = data;    

}

unsigned char usart_receive(){
  // Wait till data is received
  while (!(UCSR0A & (1<<RXC0)));

  // Get the data
  return UDR0;
}


int main(){

  usart_init();
  char data_rec[256];
  char data_snd[256];

  char name1[] = "W.S.Gunasena E/13/120";
  char name2[] = "A.A.D.K.P.Amarasinghe E/13/010";
  char name3[] = "E.L.Y.Tharaka E/13/363";

  while(1){

    char ch;
    int i=0;
    int count;

    // receive untill \n
    while((ch=usart_receive()) != '\r'){
      data_rec[i]=ch;
      i++;
    }
    count=i;

    // Transmit
    for(i=0; i<count; i++){
      usart_send(data_rec[i]);
    }

    // ch = usart_receive();

    // // usart_send('r');
    // for(i=0; i<sizeof(name1); i++){
    //  usart_send(name1[i]);
    // }

    // for(i=0; i<sizeof(name2); i++){
    //  usart_send(name2[i]);
    // }

    // for(i=0; i<sizeof(name3); i++){
    //  usart_send(name3[i]);
    // }
  }

  return 0;
}