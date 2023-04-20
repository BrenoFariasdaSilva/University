//-----------------------------------------------------------------------------------
#define F_CPU 16000000UL	//define a frequência do microcontrolador em 16MHz
#include <avr/io.h> 	 	//definições do componente especificado
#include <util/delay.h>		//biblioteca para o uso das rotinas de _delay_
#include <avr/pgmspace.h>	//biblioteca para poder gravar dados na memória flash 

//Definições de macros - para o trabalho com os bits de uma variável
#define tst_bit(Y,bit_x) (Y&(1<<bit_x)) //testa o bit x da variável Y (retorna 0 ou 1)
#define cpl_bit(Y,bit_x)(Y^=(1<<bit_x))
#define clr_bit(Y,bit_x)(Y&=~(1<<bit_x))
#define set_bit(Y,bit_x) (Y|=(1<<bit_x))

#define DDISPLAY	PORTD 
#define CDISPLAY	PORTC

//variável gravada na memória flash
const unsigned char Tabela[] PROGMEM = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78, 0x00, 0x18, 0x08, 0x03, 0x46, 0x21, 0x06, 0x0E};
//-----------------------------------------------------------------------------------

char unidadeBotaoEsquerdo=0,dezenaBotaoEsquerdo=0;
char unidadeBotaoDireito=0,dezenaBotaoDireito=0;
char T4=9, T3=5, T2=9;

unsigned char valorBotaoEsquerdo = 0;//declara variável
unsigned char valor1 = 0;//declara variável
unsigned char valorSegundos = 59;//declara variável
unsigned char valorUnidadeMinuto = 9;//declara variável

#define debounceInterval  1 //ms
unsigned int debounceTime = 0;
int contador = 0;//CONTADOR PARA O CRONOMETRO
int contadorAux = 0;
int lastState = 1;// ultima leitura com ruido
int lastState1 = 1;// ultima leitura com ruido
int botao = 1;// estado do botao
int botao1 = 1;// estado do botao

//-----------------------------------------------------------------------------------
void setDisplay(int val){
  	unsigned char disp = pgm_read_byte(&Tabela[val]);
    DDISPLAY &=  0b00001111;
    DDISPLAY |= (0b11110000 & (disp << 4));
    CDISPLAY &=  0b11111000;
    CDISPLAY |= (0b00000111 & (disp >> 4));
} 

void setup()
{
  DDRD |= 0b11110000; // PD4 até PD7 como saída
  DDRC |= 0b00000111; // PC0 até PC2 como saída
  DDRB = 0b11111111; //PORTB como saída (para enviar informação aos displays)
  DDRC |= 0b11001111;//PC5 e PC4 como pinos de entrada, demais como saída;
  
  //BOTÃO 1:
  PORTC |= (1<<PC5); // PC5 pull-up
  //BOTÃO 2:
  PORTC |= (1<<PC4); // PC4 pull-up
	 
  DDRD = 0xFF;		//PORTD como saída (display)
  PORTD= 0xFF;		//desliga o display
  UCSR0B = 0x00;	//PD0 e PD1 como I/O genérico, para uso no Arduino

  DDRB |= (1<<PB5)|(1<<PB4); // anodo dos displays como saida
  PORTB &= ~(1<<PB5)&(~(1<<PB4)); // displays desligados
}
 
//-----------------------------------------------------------------------------------
void loop(){ //laço infinito
  
  int leitura = PINC & (1<<PC5);
  int leitura1 = PINC & (1<<PC4);
  
  if(valorSegundos == 0 && valorUnidadeMinuto == 0){//Verifica se o cronometro está zerado e desabilita os botões
   	leitura = -1;
  		leitura1 = -1;
  }
  
  if ((leitura != lastState) || (leitura1 != lastState1))debounceTime = millis();
  
  contadorAux = contador; //Contador auxliar salva o estado anterior do contador
  int temp = millis();
  contador = temp/1000;//Contador é atualizado
  
  //Conjunto de Display A
  if ((millis() - debounceTime) > debounceInterval) {
    if (botao != leitura) {
      botao = leitura;
      if (botao == 0) {
       if(valorBotaoEsquerdo==99)	 
			valorBotaoEsquerdo=0;
        else{ 				
			valorBotaoEsquerdo++;
            unidadeBotaoEsquerdo = valorBotaoEsquerdo%10;
          	dezenaBotaoEsquerdo = valorBotaoEsquerdo/10; 
        }
      }
    }
  }
  
  //Conjunto de Display B
  if ((millis() - debounceTime) > debounceInterval) {
    if (botao1 != leitura1) {
      botao1 = leitura1;
      if (botao1 == 0) {
       if(valor1==99)	
			valor1=0;
        else{ 				
			valor1++;
            unidadeBotaoDireito = valor1%10;
          	dezenaBotaoDireito = valor1/10; 
        }
      }
    }
  }
    
  lastState = leitura;
  lastState1 = leitura1;

  //decodifica o valor e mostra no display, busca o valor na Tabela.
  PORTB |= (1<<PB4); 
  setDisplay(unidadeBotaoEsquerdo);
  _delay_ms(5);
  PORTB &= ~(1<<PB4);
  
  PORTB |= (1<<PB5);
  setDisplay(dezenaBotaoEsquerdo);
  _delay_ms(5);
  PORTB &= ~(1<<PB5);
  
  //Display B
  PORTB |= (1<<PB2); 
  setDisplay(unidadeBotaoDireito);
  _delay_ms(5);
  PORTB &= ~(1<<PB2);
  
  PORTB |= (1<<PB3);
  setDisplay(dezenaBotaoDireito);
  _delay_ms(5);
  PORTB &= ~(1<<PB3);
  
  
  //Cronometro
  T2 = valorSegundos%10;
  T3 = valorSegundos/10;
  T4 = valorUnidadeMinuto%10;
  
  PORTB |= (1<<PB0); 
  setDisplay(T3);
  _delay_ms(1);
  PORTB &= ~(1<<PB0);
  
  PORTB |= (1<<PB1);
  setDisplay(T2);
  _delay_ms(1);
  PORTB &= ~(1<<PB1);
  
  PORTC |= (1<<PC3);
  setDisplay(T4);
  _delay_ms(1);
  PORTC &= ~(1<<PC3);

  if(contador == contadorAux+1){ //Verifica se passou um segundo
    if(valorSegundos > 0)valorSegundos--;
    if(valorSegundos == 0 && valorUnidadeMinuto != 0){//Se passou 59 segundos decrementa o minuto
      valorSegundos = 59;
      valorUnidadeMinuto--;
    }
  }
}
//===================================================================================