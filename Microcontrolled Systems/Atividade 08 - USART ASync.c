
#define F_CPU 16000000UL  //define a frequencia do microcontrolador - 16MHz

#include <avr/io.h>       //definições do componente especificado
#include <util/delay.h>   //biblioteca para o uso das rotinas de _delay_ms e _delay_us()
#include <avr/pgmspace.h>   //para o uso do PROGMEM, gravação de dados na memória flash
#include <stdio.h>
#include <string.h>
#define F_CPU 16000000UL  //define a frequencia do microcontrolador - 16MHz

#include <avr/io.h>       //definições do componente especificado
#include <util/delay.h>   //biblioteca para o uso das rotinas de _delay_ms e _delay_us()
#include <avr/pgmspace.h>   //para o uso do PROGMEM, gravação de dados na memória flash
#include <stdio.h>
#include <string.h>

//Definições de macros - para o trabalho com os bits de uma variável
#define tst_bit(Y,bit_x) (Y&(1<<bit_x)) //testa o bit x da variável Y (retorna 0 ou 1)
#define cpl_bit(Y,bit_x)(Y^=(1<<bit_x))
#define clr_bit(Y,bit_x)(Y&=~(1<<bit_x))
#define set_bit(Y,bit_x) (Y|=(1<<bit_x))

#define BAUD   2400    //taxa de 2400 bps
#define MYUBRR  F_CPU/16/BAUD-1

#define LEDB4 PB4 
#define LEDB5 PB5

#define BUFFLEN 32
#define RECIEVEBUFFER 3
// buffer de dados de envio na porta serial
char buff[BUFFLEN];
// pos indica a posição corrente no buffer
// end indica a posição final no buffer com dados válidos
// note que end pode ser menor que pos, já que o buffer é circular
// cntbuff indica quantos caracteres válidos há no buffer
short pos=0,end=0,cntbuff=0;

char async_buffer[BUFFLEN] = {0};
char async_buffer_recieve[RECIEVEBUFFER] = {0};
int temporizadorInicial = 0; 
int temporizadorFinal = 0; 
char* tempo = 0; //variavel temporizador final - inicial

//---------------------------------------------------------------------------
void USART_Inic(unsigned int ubrr0)
{
  UBRR0H = (unsigned char)(ubrr0>>8); //Ajusta a taxa de transmissão
  UBRR0L = (unsigned char)ubrr0;

  UCSR0A = 0;//desabilitar velocidade dupla (no Arduino é habilitado por padrão)
  UCSR0B = (1<<RXEN0)|(1<<TXEN0); //Habilita a transmissão e a recepção
  UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);/*modo assíncrono, 8 bits de dados, 1 bit de parada, sem paridade*/
  UCSR0B |= (1<<RXCIE0);
  
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

void USART_tx_async(char *buff)
{
  UDR0 = buff[0]; //atribui na porta serial
  memcpy(async_buffer, ++buff,strlen(buff)); //copia o millis para o buffer
  UCSR0B |= (1<<UDRIE0); //habilita interrupcao usart
}

ISR(USART_RX_vect) {
	async_buffer_recieve[0] = async_buffer_recieve[1];
  	async_buffer_recieve[1] = async_buffer_recieve[2];
	async_buffer_recieve[2] = UDR0; // Recebe o dado do serial
  
	if(!strcmp("A13", async_buffer_recieve) || !strcmp("a13", async_buffer_recieve))
		set_bit(PORTB,PB5); // A13 acende o led em PB5
	if(!strcmp("S13", async_buffer_recieve) || !strcmp("s13", async_buffer_recieve))
		clr_bit(PORTB,PB5); // S13 apaga o led em PB5
	if(!strcmp("D12", async_buffer_recieve) || !strcmp("d12", async_buffer_recieve))
		cpl_bit(PORTB,PB4); // D12 altera o estado do led em PB4
}

// millis no serial
void envia_millis(unsigned long mil) {
  char sendText[20] = {0};
  sprintf(sendText, "%u\n", mil);
  EscreveAsync(sendText, strlen(sendText));
}

int main()
{  
  DDRB |= (1<<LEDB4)|(1<<LEDB5); //somente pino do LED como saída
  PORTB = 0b111000111; //pull up//apaga LED e habilita pull-ups nos pinos não utilizados
  
  USART_Inic(MYUBRR);
  
  while(1) {
    _delay_ms(100);
  	envia_millis(millis()); // não bloqueante
  }
}
//Definições de macros - para o trabalho com os bits de uma variável
#define tst_bit(Y,bit_x) (Y&(1<<bit_x)) //testa o bit x da variável Y (retorna 0 ou 1)
#define cpl_bit(Y,bit_x)(Y^=(1<<bit_x))
#define clr_bit(Y,bit_x)(Y&=~(1<<bit_x))
#define set_bit(Y,bit_x) (Y|=(1<<bit_x))

#define BAUD   2400    //taxa de 2400 bps
#define MYUBRR  F_CPU/16/BAUD-1

#define LEDB4 PB4 
#define LEDB5 PB5

#define BUFFLEN 32
// buffer de dados de envio na porta serial
char buff[BUFFLEN];
// pos indica a posição corrente no buffer
// end indica a posição final no buffer com dados válidos
// note que end pode ser menor que pos, já que o buffer é circular
// cntbuff indica quantos caracteres válidos há no buffer
short pos=0,end=0,cntbuff=0;

// MODIFY
char async_buff[BUFFLEN];
int pressionadoI = 0; //variavel temporizador inicial
int pressionadoF = 0; //variavel temporizador final
char* tempo = 0; //variavel temporizador final - inicial

//---------------------------------------------------------------------------
void USART_Inic(unsigned int ubrr0)
{
  UBRR0H = (unsigned char)(ubrr0>>8); //Ajusta a taxa de transmissão
  UBRR0L = (unsigned char)ubrr0;

  UCSR0A = 0;//desabilitar velocidade dupla (no Arduino é habilitado por padrão)
  UCSR0B = (1<<RXEN0)|(1<<TXEN0); //Habilita a transmissão e a recepção
  UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);/*modo assíncrono, 8 bits de dados, 1 bit de parada, sem paridade*/
  UCSR0B |= (1<<RXCIE0);
  
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

void USART_tx_async(char *buff) // MODIFY
{
  UDR0 = buff[0]; //atribui na porta serial
  memcpy(async_buff, ++buff,strlen(buff)); //copia o millis para o buffer
  UCSR0B |= (1<<UDRIE0); //habilita interrupcao uart
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

ISR(USART_RX_vect) { // MODIFY
	char c = UDR0;	//char c recebe os caracteres do monitor serial (UDR0)
  
  						//Compara o char com os caracteres A,S e D
      if(c == 'A'){		//Se igual a A
      	set_bit(PORTB,PB5);		//acende o LED 1, no pino PB5
      }
  	  else if(c == 'S'){		//Se igual a S
        clr_bit(PORTB,PB5);		//Apaga o LED 1, no pino PB5
      }
  	  else if(c == 'D'){		//Se igual a D
      	cpl_bit(PORTB,PB4);		//Inverte o estado do LED2, no pino PB4
      }
  	UDR0 = '\n';				//Pula uma linha no monitor serial
    UDR0 = c;					//UDR0 mostra o caractere no monitor serial
}

//-------------------------------------------------------------------------
int main()
{  
  DDRB |= (1<<LEDB4)|(1<<LEDB5); //somente pino do LED como saída
  PORTB = 0b111000111; //pull up//apaga LED e habilita pull-ups nos pinos não utilizados
  
  USART_Inic(MYUBRR);
  
  EscreveAsync("", 14);
  _delay_ms(1);
  EscreveAsync("", 9);
  EscreveAsync("", 7);
  
  while(1) { // MODIFY
    pressionadoI = millis(); //inicia contagem millis
    
    _delay_ms(100);  //delay 0.1s
    pressionadoF = millis();  //cronometra e insere em pressionadoF
    
    itoa(pressionadoF - pressionadoI, tempo, 10); //converte tempo resultante e armazena em tempo
    //obs: nao consegui fazer ele imprimir float no serial, ele imprimia uma caixa sinalizando simbolo desconhecido.
    USART_tx_async(tempo); //chama funcao passando o millis
    
  }
}