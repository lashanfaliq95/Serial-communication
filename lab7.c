 #include <avr/io.h>
void usart_init(){
UCSR0B |=(1<<3) | (1<<4); //enable tansmission and receive
UCSR0C &= ~(1<<6); // asynchronous
UCSR0C |= (1<<2);//selecting 8 bit frame
UCSR0C |= (1<<1);
UCSR0C &= ~(1<<4);//parity diabled
UCSR0C &= ~(1<<5);
UCSR0C &= ~(1<<3);//one stop bit
UBRR0H = 0;                      // shift the register right by 8 bits
UBRR0L=103; 
}



void usart_send(char data){


while (!( UCSR0A & (1<<UDRE0)));                
    UDR0 = data; 
}

char usart_receive(){
 while(!(UCSR0A) & (1<<RXC0));                   
    return UDR0;

}


int main(void){
  usart_init();
  char data_rec[256];
  char data_snd[256]="E/13/095-M.L Faliq\nE/13/056-A.H.S.J De Silva \nE/13/132- H.L.S Hashantha";;
  while(1){
  char ch;
  int i=0;
  int count;
    


  while((ch=usart_receive())!='\r'){
  	data_rec[i]=ch;
  	i++;
  }
 count=i;
     for(i=0;i<count;i++){
 usart_send(data_snd[i]);

  }

 


  }



}