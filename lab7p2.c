#include <avr/io.h>      
#define BAUDRATE 103  
#define shift 3
void usart_init();
void usart_send(char data);
char usart_receive ();

int main(){

	usart_init();
	char data_rec[8] ;
	char data_snd[8];
	data_snd[0]=65;
	data_snd[1]=66;
	data_snd[2]=0;
	data_snd[3]=97;
	data_snd[4]=98;
	data_snd[5]=122;
	data_snd[6]=0;
	data_snd[7]=9;
	
	while(1) {
		
		//char ch='A' ;
		char chR;
		int i = 0 ;
		int count ;
		
		
		//transmit
		for(i = 0;i < sizeof(data_snd) ; i++){

                 if(data_snd[i]>=65 && data_snd[i]<=90){
                 	 if(data_snd[i]+shift>90)
                 	 	usart_send(data_snd[i]+shift-26);
                 	 else
                 	 	usart_send(data_snd[i]+shift);
                 	 }

			 else if(data_snd[i]>=97 && data_snd[i]<=122){
			     	 if(data_snd[i]+shift>122)
                 	 	usart_send(data_snd[i]+shift-26);
                 	 else
                 	 	usart_send(data_snd[i]+shift);
                 	}

                 	else{
					usart_send(data_snd[i]);}
		}
		
		// receive characters until \n
		while ((chR = usart_receive())!= '\r'){
			data_rec[i] = chR ;
			i++ ;
			
		}
		count = i;
		
		
		
	}

}


void usart_init()
{
	/*Set baud rate */
    //UBRR0H = (BAUDRATE>>8);                      // shift the register right by 8 bits
    UBRR0L = BAUDRATE;                           // set baud rate
    UCSR0B|= (1<<TXEN0)|(1<<RXEN0);                // enable receiver and transmitter
    UCSR0C|= (3<<UCSZ00)|(0<<USBS0);   // 8bit data format,one stop bit
}


// function to send data
void usart_send(char data)
{
    while (!( UCSR0A & (1<<UDRE0)));                // wait while register is free
    UDR0 = data;                                   // load data in the register
}


// function to receive data
char usart_receive ()
{
    while(!(UCSR0A) & (1<<RXC0));                   // wait while data is being received
    return UDR0;                                   // return 8-bit data
}
