#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

//Definicoes de macros - empregadas para o trabalho com bits
#define	set_bit(Y,bit_x) (Y|=(1<<bit_x))	//ativa o bit x da variavel
#define	clr_bit(Y,bit_x) (Y&=~(1<<bit_x))	//limpa o bit x da variavel 
#define tst_bit(Y,bit_x) (Y&(1<<bit_x))  	//testa o bit x da variavel
#define cpl_bit(Y,bit_x) (Y^=(1<<bit_x))	//troca o estado do bit x 

#define LEDB3 PB3
#define LEDB4 PB4 
#define LEDB5 PB5

ISR(INT0_vect);
ISR(INT1_vect);

//-------------------------------------------------------------------------------------
int main()
{
  	//	PB1
    DDRB  = 0b00111010; 	//somente pino do LED como saida
	PORTB = 0xFF; 			//pull-ups habilitados na porta B
  	
  	//	PC3
  	DDRC  = 0b00000100; 	//somente pino do LED como saida
	PORTC = 0xFF; 			//pull-ups habilitados na porta C
  
  	//	PD7
	DDRD  = 0b10000000; 	//somente pino do LED como saida
	PORTD = 0xFF;			//desliga LED e habilita pull-ups 
	
	UCSR0B = 0x00;			//necessario desabilitar RX e TX para trabalho com os pinos do PORTD no Arduino	

  	PCICR |= 1<<PCIE0;		//habilita interrupcao por qualquer mudança de sinal no PORTC
  	PCICR |= 1<<PCIE1;		//habilita interrupcao por qualquer mudança de sinal no PORTC
  	PCICR |= 1<<PCIE2;		//habilita interrupcao por qualquer mudança de sinal no PORTC
  
	EICRA = 1<<ISC01;      	//interrupcoes externas: INT0 na borda de descida, INT1 no nivel zero.
  
	PCMSK0 = (1<<PCINT1);	//habilita o pino PCINT1 para gerar interrupçao
  	PCMSK1 = (1<<PCINT11);	//habilita o pino PCINT11 para gerar interrupçao
  	PCMSK2 = (1<<PCINT23);	//habilita o pino PCINT23 para gerar interrupçao

	EIMSK = (1<<INT0);		//habilita a interrupcao INT0
	
	sei();					//habilita interrupçoes globais, ativando o bit I do SREG
	
	while(1){}
}

ISR(PCINT0_vect)				//interrupçao externa 0, quando o botao eh pressionado o LED troca de estado
{
  if(!tst_bit(PINB,PB1))
  	cpl_bit(PORTB,LEDB3);
}

ISR(PCINT1_vect)				//interrupçao externa 0, quando o botao eh pressionado o LED troca de estado
{
  if(!tst_bit(PINC,PC3))
  	cpl_bit(PORTB,LEDB4);
}

ISR(PCINT2_vect)				//interrupçao externa 0, quando o botao eh pressionado o LED troca de estado
{
  if(!tst_bit(PIND,PD7))
  	cpl_bit(PORTB,LEDB5);
}

ISR(INT0_vect)
{
  //desliga todos os LEDs se eles estiverem ativos
  if((tst_bit(PORTB,LEDB3)||(tst_bit(PORTB,LEDB4))||(tst_bit(PORTB,LEDB5))))
  {
    clr_bit(PORTB,LEDB3);
    clr_bit(PORTB,LEDB4);
    clr_bit(PORTB,LEDB5);
  }
  
  //liga todos os LEDs se eles estiverem desligados
  else
  { 
    set_bit(PORTB,LEDB3);
    set_bit(PORTB,LEDB4);
    set_bit(PORTB,LEDB5);
  }
}