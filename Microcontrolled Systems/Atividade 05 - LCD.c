#ifndef _DEF_PRINCIPAIS_H
#define _DEF_PRINCIPAIS_H

#define F_CPU 16000000UL  //define a frequencia do microcontrolador - 16MHz

#include <avr/io.h>       //definições do componente especificado
#include <util/delay.h>   //biblioteca para o uso das rotinas de _delay_ms e _delay_us()
#include <avr/pgmspace.h>   //para o uso do PROGMEM, gravação de dados na memória flash

//Definições de macros para o trabalho com bits

#define set_bit(y,bit)  (y|=(1<<bit)) //coloca em 1 o bit x da variável Y
#define clr_bit(y,bit)  (y&=~(1<<bit))  //coloca em 0 o bit x da variável Y
#define cpl_bit(y,bit)  (y^=(1<<bit)) //troca o estado lógico do bit x da variável Y
#define tst_bit(y,bit)  (y&(1<<bit))  //retorna 0 ou 1 conforme leituraBotaoEsquerdo do bit

#endif

#ifndef _LCD_H
#define _LCD_H

//#include "def_principais.h"

//Definições para facilitar a troca dos pinos do hardware e facilitar a re-programação

#define DADOS_LCD      PORTC   //4 bits de dados do LCD no PORTD 
#define nibble_dados  0   //0 para via de dados do LCD nos 4 LSBs do PORT empregado (Px0-D4, Px1-D5, Px2-D6, Px3-D7) 
								//1 para via de dados do LCD nos 4 MSBs do PORT empregado (Px4-D4, Px5-D5, Px6-D6, Px7-D7) 
#define CONTR_LCD     PORTC   //PORT com os pinos de controle do LCD (pino R/W em 0).
#define E         PC4     //pino de habilitação do LCD (enable)
#define RS        PC5     //pino para informar se o dado é uma instrução ou caractere

#define tam_vetor 5 //número de digitos individuais para a conversão por ident_num()   
#define conv_ascii  48  //48 se ident_num() deve retornar um número no formato ASCII (0 para formato normal)

// Defines e Variáveis globais relativas ao código dos botões e do cronometro.
//variável gravada na memória flash

unsigned char valorBotaoEsquerdo = 0;//declara variável
unsigned char valorBotaoDireito = 0;//declara variável

unsigned char valorUnidadeMinuto = 9;//declara variável
int valorSegundos = 59;//declara variável
int valorCentesimos = 99;//declara variável

#define debounceInterval  1 //ms
unsigned long debounceTimeBotaoEsquerdo = 0;
unsigned long debounceTimeBotaoDireito = 0; 

int lastStatebotaoEsquerdo = 1;// ultima leituraBotaoEsquerdo com ruido
int lastStatebotaoDireito = 1;// ultima leituraBotaoEsquerdo com ruido

int botaoEsquerdo = 1;// estado do botaoEsquerdo
int botaoDireito = 1;// estado do botaoEsquerdo

double contadorAtual = 0; // CONTADOR PARA O CRONOMETRO
double contadorAnterior = 0; // CONTADOR AUXILIAR PARA O CRONOMETRO

//sinal de habilitação para o LCD
#define pulso_enable()  _delay_us(1); set_bit(CONTR_LCD,E); _delay_us(1); clr_bit(CONTR_LCD,E); _delay_us(45)

//protótipo das funções
void cmd_LCD(unsigned char c, char cd);
void inic_LCD_4bits();    
void escreve_LCD(char *c);
void escreve_LCD_Flash(const char *c);

void ident_num(unsigned int valor, unsigned char *disp);

#endif

//--------------------------------------------------------------------------------------------- //
//    AVR e Arduino: Técnicas de Projeto, 2a ed. - 2012.                    //  
//--------------------------------------------------------------------------------------------- //
//============================================================================================= //
//    Sub-rotinas para o trabalho com um LCD 16x2 com via de dados de 4 bits          //  
//    Controlador HD44780 - Pino R/W aterrado                         //
//    A via de dados do LCD deve ser ligado aos 4 bits mais significativos ou         //
//    aos 4 bits menos significativos do PORT do uC                     //                                
//============================================================================================= //
// #include "LCD.h"

//---------------------------------------------------------------------------------------------
// Sub-rotina para enviar caracteres e comandos ao LCD com via de dados de 4 bits
//---------------------------------------------------------------------------------------------

void cmd_LCD(unsigned char c, char cd)        //c é o dado  e cd indica se é instrução ou caractere
{
	if (cd==0)
		clr_bit(CONTR_LCD,RS);
	else
		set_bit(CONTR_LCD,RS);

	//primeiro nibble de dados - 4 MSB
	#if (nibble_dados)                //compila código para os pinos de dados do LCD nos 4 MSB do PORT
		DADOS_LCD = (DADOS_LCD & 0x0F)|(0xF0 & c);    
	#else                     //compila código para os pinos de dados do LCD nos 4 LSB do PORT
		DADOS_LCD = (DADOS_LCD & 0xF0)|(c>>4);  
	#endif

	pulso_enable();

	//segundo nibble de dados - 4 LSB
	#if (nibble_dados)                //compila código para os pinos de dados do LCD nos 4 MSB do PORT
		DADOS_LCD = (DADOS_LCD & 0x0F) | (0xF0 & (c<<4));   
	#else                     //compila código para os pinos de dados do LCD nos 4 LSB do PORT
		DADOS_LCD = (DADOS_LCD & 0xF0) | (0x0F & c);
	#endif

	pulso_enable();

	if ((cd==0) && (c<4))        //se for instrução de retorno ou limpeza espera LCD estar pronto
		_delay_ms(2);
}

//---------------------------------------------------------------------------------------------
//Sub-rotina para inicialização do LCD com via de dados de 4 bits
//---------------------------------------------------------------------------------------------

void inic_LCD_4bits()   //sequência ditada pelo fabricando do circuito integrado HD44780
{          							//o LCD será só escrito. Então, R/W é sempre zero.
	clr_bit(CONTR_LCD,RS);  //RS em zero indicando que o dado para o LCD será uma instrução 
	clr_bit(CONTR_LCD,E); //pino de habilitação em zero

	_delay_ms(20);      //tempo para estabilizar a tensão do LCD, após VCC ultrapassar 4.5 V (na prática pode
					//ser maior). 
	//interface de 8 bits           
	#if (nibble_dados)
		DADOS_LCD = (DADOS_LCD & 0x0F) | 0x30;    
	#else   
		DADOS_LCD = (DADOS_LCD & 0xF0) | 0x03;    
	#endif            
					
	pulso_enable();     //habilitação respeitando os tempos de resposta do LCD
	_delay_ms(5);   
	pulso_enable();
	_delay_us(200);
	pulso_enable(); /*até aqui ainda é uma interface de 8 bits.
										Muitos programadores desprezam os comandos acima, respeitando apenas o tempo de
										estabilização da tensão (geralmente funciona). Se o LCD não for inicializado primeiro no 
										modo de 8 bits, haverá problemas se o microcontrolador for inicializado e o display já o tiver sido.*/

	//interface de 4 bits, deve ser enviado duas vezes (a outra está abaixo)
	#if (nibble_dados) 
		DADOS_LCD = (DADOS_LCD & 0x0F) | 0x20;    
	#else   
		DADOS_LCD = (DADOS_LCD & 0xF0) | 0x02;
	#endif
	
	pulso_enable();   	
	cmd_LCD(0x28,0);    //interface de 4 bits 2 linhas (aqui se habilita as 2 linhas) 
	//são enviados os 2 nibbles (0x2 e 0x8)
	cmd_LCD(0x08,0);    //desliga o display
	cmd_LCD(0x01,0);    //limpa todo o display
	cmd_LCD(0x0C,0);    //mensagem aparente cursor inativo não piscando   
	cmd_LCD(0x80,0);    //inicializa cursor na primeira posição a esquerda - 1a linha
}

//---------------------------------------------------------------------------------------------
//Sub-rotina de escrita no LCD -  dados armazenados na RAM
//---------------------------------------------------------------------------------------------

void escreve_LCD(char *c)
{
	 for (; *c!=0;c++) cmd_LCD(*c,1);
}

//---------------------------------------------------------------------------------------------
//Sub-rotina de escrita no LCD - dados armazenados na FLASH
//---------------------------------------------------------------------------------------------

void escreve_LCD_Flash(const char *c)
{
	 for (;pgm_read_byte(&(*c))!=0;c++) cmd_LCD(pgm_read_byte(&(*c)),1);
}

//---------------------------------------------------------------------------------------------
//Conversão de um número em seus digitos individuais
//---------------------------------------------------------------------------------------------

void ident_num(unsigned int valor, unsigned char *disp)
{   
	unsigned char n;

	for(n=0; n<tam_vetor; n++)
		disp[n] = 0 + conv_ascii;   //limpa vetor para armazenagem do digitos 

	do
	{
		*disp = (valor%10) + conv_ascii; //pega o resto da divisao por 10 
		valor /=10;            //pega o inteiro da divisão por 10
		disp++;
	} while (valor!=0);
}

//---------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------- //
//		AVR e Arduino: Técnicas de Projeto, 2a ed. - 2012.								//	
//------------------------------------------------------------------------------------- //
//=====================================================================================	//
//		ACIONANDO UM DISPLAY DE CRISTAL LIQUIDO DE 16x2									//
//		Uso da função ident_num(...)													//
//=====================================================================================	//

//#include "def_principais.h"	//inclusão do arquivo com as principais definições 
//#include "LCD.h"

//-------------------------------------------------------------------------------------

void setup()
{
	DDRC = 0xFF;						//PORTC como saída
	DDRD = 0xFF; 						//PORTD como saída
	
	// Botões
	DDRD = 0b11001111;//PD5 e PD4 como pinos de entrada, demais como saída;

	//BOTÃO 1:
	PORTD |= (1<<PD5); // PD5 pull-up
	//BOTÃO 2:
	PORTD |= (1<<PD4); // PD4 pull-up
	 
	inic_LCD_4bits();					//inicializa o LCD
}

void loop() // Laço Infinito
{ 
	unsigned char digitos[tam_vetor];	//declaração da variável para armazenagem dos digitos

	int leituraBotaoEsquerdo = (PIND & (1<<PD5)); // leituraBotaoEsquerdo do botão 1
	int leituraBotaoDireito = (PIND & (1<<PD4)); // leituraBotaoEsquerdo do botão 2

	if (valorSegundos == 0 && valorUnidadeMinuto == 0 && valorCentesimos == 0) { //Verifica se o cronometro está zerado e desabilita os botões
		leituraBotaoEsquerdo = -1; //PD5
		leituraBotaoDireito = -1; //PD4
	}

	if (leituraBotaoEsquerdo != lastStatebotaoEsquerdo)
		debounceTimeBotaoEsquerdo = millis(); // atualiza o tempo do botão

	if (leituraBotaoDireito != lastStatebotaoDireito)
		debounceTimeBotaoDireito = millis(); // atualiza o tempo do botão

	contadorAnterior = contadorAtual; // Contador auxliar salva o estado anterior do contador
	long tempoAtual = millis(); //Tempo atual
	contadorAtual = tempoAtual/1000; // Contador é atualizado

	// Conjunto do Botão Esquerdo
	if ((tempoAtual - debounceTimeBotaoEsquerdo) > debounceInterval) { // se o tempo de debounce for maior que o intervalo de debounce
		if (botaoEsquerdo != leituraBotaoEsquerdo) { // se o botão for pressionado 
			botaoEsquerdo = leituraBotaoEsquerdo; // atualiza o estado do botão
			if (botaoEsquerdo == 0) { // se o botão for pressionado
				if (valorBotaoEsquerdo==99) //se o valor for 0, o valor volta ao fim
					valorBotaoEsquerdo=0; //se o valor for 0, o valor passa a ser 99
				else			 //se o valor for diferente de 0
					valorBotaoEsquerdo++; //incrementa o valor
			}
		}
	}

	lastStatebotaoEsquerdo = leituraBotaoEsquerdo; // atualiza o estado do botão

	//Conjunto do Botão Direito
	if ((tempoAtual - debounceTimeBotaoDireito) > debounceInterval) { // se o tempo de debounce for maior que o intervalo de debounce
		if (botaoDireito != leituraBotaoDireito) { // se o botão for pressionado 
			botaoDireito = leituraBotaoDireito; // atualiza o estado do botão
			if (botaoDireito == 0) { // se o botão for pressionado
				if (valorBotaoDireito==99) //se o valor for 99, o valor volta ao inicio
					valorBotaoDireito=0; //se o valor for 99, o valor passa a ser 0
				else			 //se o valor for diferente de 99
					valorBotaoDireito++; //incrementa o valor
			}
		}
	}

	lastStatebotaoDireito = leituraBotaoDireito; // atualiza o estado do botão
		
	digitos[4] = (valorUnidadeMinuto%10) + '0'; //converte o valor de T4 para caractere
	digitos[3] = (valorSegundos/10) + '0'; //converte o valor de T3 para caractere
	digitos[2] = (valorSegundos%10) + '0'; //converte o valor de T2 para caractere
	digitos[1] = (valorCentesimos/10) + '0'; //Adicionar a dezena do milésimo de segundo
	digitos[0] = (valorCentesimos%10) + '0'; //Adicionar a unidade do milésimo de segundo

	cmd_LCD(0x80,0);	// Desloca o cursor para que fiquem a esquerda do LCD
		
	// Valores dos pontos do placar da esquerda
	cmd_LCD((valorBotaoEsquerdo/10) + '0',1); //converte o valor de dezenaBotaoEsquerdo para caractere e escreve no LCD
	cmd_LCD((valorBotaoEsquerdo%10) + '0',1); //converte o valor de unidadeBotaoEsquerdo para caractere e escreve no LCD

	cmd_LCD(' ',1); // Espaços em branco para melhorar a legibilidade
	cmd_LCD(' ',1); // Espaços em branco para melhorar a legibilidade
		
	cmd_LCD('0',1); // Valor estático '0' na dezena dos minutos para melhor formatação
	cmd_LCD(digitos[4],1);  // Escreve o valor da unidade do minutos no LCD
	cmd_LCD(':',1);  // Escreve o caractere ':' no LCD
	cmd_LCD(digitos[3],1); // Escreve o valor da dezena dos segundos no LCD
	cmd_LCD(digitos[2],1); // Escreve o valor da unidade dos segundos no LCD
	cmd_LCD(':',1); // Espaço : para formatação do LCD
	cmd_LCD(digitos[1],1); // Escreve o valor da dezena dos centésimos de segundo no LCD
	cmd_LCD(digitos[0],1); // Escreve o valor da unidade dos centésimos de segundo no LCD

	cmd_LCD(' ',1); // Espaços em branco para melhorar a legibilidade
	cmd_LCD(' ',1); // Espaços em branco para melhorar a legibilidade

	// Valores dos pontos do placar da direita
	cmd_LCD((valorBotaoDireito/10) + '0', 1); // converte o valor da dezena do botão da direita para caractere e escreve no LCD
	cmd_LCD((valorBotaoDireito%10) + '0', 1); // converte o valor de unidade do botão da direita para caractere e escreve no LCD
	
	if (contadorAtual == contadorAnterior + 1){ //Verifica se passou um segundo
		if (valorSegundos > 0)
			valorSegundos--; //Decrementa o valor do tempo

		if (valorSegundos == 0 && valorUnidadeMinuto != 0){ //Se passou 59 segundos decrementa o minuto
			valorSegundos = 59; //Valor do tempo volta ao inicio
			valorUnidadeMinuto--; //Decrementa o valor do minuto
		}
	}
  
    valorCentesimos = 99 - ((millis() / 10) % 100);
  	// _delay_ms(15);
}