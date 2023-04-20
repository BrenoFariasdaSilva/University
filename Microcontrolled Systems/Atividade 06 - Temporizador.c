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

ISR(TIMER0_OVF_vect) //interrupção do TC0
{
	cpl_bit(PORTB,LEDB3);//Liga o LED em PB3
}

ISR(TIMER1_OVF_vect) //interrupção do TC1
{
 	cpl_bit(PORTB,LEDB4);//Liga o LED em PB4
}

ISR(TIMER2_OVF_vect) //interrupção do TC2
{
 	cpl_bit(PORTB,LEDB5);//Liga o LED em PB5
}

int main()
{
 	DDRB |= (1<<LEDB3)|(1<<LEDB4)|(1<<LEDB5); //somente pino do LED como saída
    PORTB = 0b111000111; //pull up//apaga LED e habilita pull-ups nos pinos não utilizados
      
  	// Timer 0
  	TCCR0A = 0b01010010;
  	TCCR0B = (1<<CS02) | (1<<CS00); //TC0 com prescaler de 1024
  	TIMSK0 = 1<<TOIE0; 				//habilita a interrupção do TC0
  	OCR0A = 155; 					//Uma interrupção a cada 9.984ms
  
  	// Timer 1
  	TCCR1A = (1<<WGM12)|(1<<COM1A0);
  	TCCR1B = (1<<CS12); //TC1 com prescaler de 256
  	OCR1A = 62374;		//Uma interrupção a cada 998ms
  	TIMSK1 = 1<<TOIE1;	//habilita a interrupção do TC1
  
  	// Timer 2
  	TCCR2A |= (1<<WGM21)|(1<<WGM20); //Modo rápido do PWM
    TCCR2B |= (1<<CS21)|(1<<CS20);   //TC2 com prescaler de 32	         
  	OCR2A = 1249999;                //Uma interrupção a cada 2500ms
  	
  	sei(); //habilita a chave de interrupção global
	while(1);
  	return 0;
}
