#ifndef _LCD_H
#define _LCD_H

#include "def_principais.h"

//Defini��es para facilitar a troca dos pinos do hardware e facilitar a re-programa��o

#define DADOS_LCD    	PORTD  	//4 bits de dados do LCD no PORTD 
#define nibble_dados	1		//0 para via de dados do LCD nos 4 LSBs do PORT empregado (Px0-D4, Px1-D5, Px2-D6, Px3-D7) 
								//1 para via de dados do LCD nos 4 MSBs do PORT empregado (Px4-D4, Px5-D5, Px6-D6, Px7-D7) 
#define CONTR_LCD 		PORTB  	//PORT com os pinos de controle do LCD (pino R/W em 0).
#define E    			PB1     //pino de habilita��o do LCD (enable)
#define RS   			PB0     //pino para informar se o dado � uma instru��o ou caractere

#define tam_vetor	5	//n�mero de digitos individuais para a convers�o por ident_num()	 
#define conv_ascii	48	//48 se ident_num() deve retornar um n�mero no formato ASCII (0 para formato normal)

//sinal de habilita��o para o LCD
#define pulso_enable() 	_delay_us(1); set_bit(CONTR_LCD,E); _delay_us(1); clr_bit(CONTR_LCD,E); _delay_us(45)

//prot�tipo das fun��es
void cmd_LCD(unsigned char c, char cd);
void inic_LCD_4bits();		
void escreve_LCD(char *c);
void escreve_LCD_Flash(const char *c);

void ident_num(unsigned int valor, unsigned char *disp);

#endif

