#define F_CPU 16000000UL  //define a frequencia do microcontrolador - 16MHz

#include <avr/io.h>       //definições do componente especificado
#include <util/delay.h>   //biblioteca para o uso das rotinas de _delay_ms e _delay_us()
#include <avr/pgmspace.h>   //para o uso do PROGMEM, gravação de dados na memória flash
#include <stdio.h>
#include <string.h>


#define BAUD   2400    //taxa de 2400 bps
#define MYUBRR  F_CPU/16/BAUD-1

#define BUFFLEN 32
// buffer de dados de envio na porta serial
char buff[BUFFLEN];
char receptBuffer[4] = {0};
// pos indica a posição corrente no buffer
// end indica a posição final no buffer com dados válidos
// note que end pode ser menor que pos, já que o buffer é circular
// cntbuff indica quantos caracteres válidos há no buffer
short pos=0,end=0,cntbuff=0;

//---------------------------------------------------------------------------
void USART_Inic(unsigned int ubrr0)
{
  UBRR0H = (unsigned char)(ubrr0>>8); //Ajusta a taxa de transmissão
  UBRR0L = (unsigned char)ubrr0;

  UCSR0A = 0;//desabilitar velocidade dupla (no Arduino é habilitado por padrão)
  UCSR0B |= (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);
  UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);/*modo assíncrono, 8 bits de dados, 1 bit de parada, sem paridade*/

  
  
  sei();
}

//---------------------------------------------------------------------------
void EscreveAsync(char *dados, short len) {
  // desabilita temporariamente interrupção
  UCSR0B &= ~(1<<UDRIE0);
  // não deixa enfileirar mais dados que o tamanho do buffer
  len %= BUFFLEN;
  
  // separa a cópia dos dados para o buffer em duas
  // partes se necessário for
  cntbuff += len;
  short cnt = BUFFLEN-end; 
  cnt = cnt>len?len:cnt;
  
  memcpy(buff+end, dados, cnt);
  if (cnt<len)
    memcpy(buff, dados+cnt, len-cnt);
  
  end += len;
  end %= BUFFLEN;
  // habilita interrupção para (re)iniciar o envio
  UCSR0B |= (1<<UDRIE0);
}

//---------------------------------------------------------------------------

void envia_millis(unsigned long mil) {
  char millisStr[12];
  sprintf(millisStr, "%lu\n", mil);
  EscreveAsync(millisStr, strlen(millisStr));
}

//---------------------------------------------------------------------------
ISR(USART_UDRE_vect) {
  // enquanto houver dados no buffer
  if (cntbuff>0) {
    UDR0 = buff[pos]; // envia
    pos++;
    cntbuff--;
    pos %= BUFFLEN; // buffer circular
  } else {
    // se não houver o que enviar, desliga interrupção
    UCSR0B &= ~(1<<UDRIE0);
  }
}
            
ISR(USART_RX_vect) {
  receptBuffer[0] = receptBuffer[1];
  receptBuffer[1] = receptBuffer[2];
  receptBuffer[2] = UDR0; // Recebe o dado do serial	
  
  if(!strcmp(receptBuffer, "A13")){
    PORTB |= 0b00100000; 
  } else if(!strcmp(receptBuffer, "S13")){
    PORTB = 0b00000000; 
  } else if(!strcmp(receptBuffer, "D12")){
    PORTB ^= 0b00010000; 
  }
}


//-------------------------------------------------------------------------
int main() {
  
  	init();
  
  	DDRB |= (1<<PB4)| (1<<PB5);	//define PB4 e PB5 como saída
  
  	USART_Inic(MYUBRR);
  
	while(1) {
  		_delay_ms(100);
  		envia_millis(millis()); // não bloqueante
	}	
}

