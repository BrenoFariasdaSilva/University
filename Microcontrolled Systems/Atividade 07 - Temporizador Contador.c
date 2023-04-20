#define F_CPU 16000000UL	//define a frequência do microcontrolador em 16MHz

#include <avr/io.h> 	 	//definições do componente especificado
#include <util/delay.h>		//biblioteca para o uso das rotinas de _delay_
#include <avr/pgmspace.h>	//biblioteca para poder gravar dados na memória flash 

//Definições de macros - para o trabalho com os bits de uma variável
#define tst_bit(Y,bit_x) (Y&(1<<bit_x)) //testa o bit x da variável Y (retorna 0 ou 1)
#define set_bit(Y,bit_x) (Y|=(1<<bit_x))
#define clr_bit(Y,bit_x) (Y&=~(1<<bit_x))

#define debounceInterval 200 // ms
#define DISPLAY	 PORTD		//define um nome auxiliar para o display  
#define BOTAOESQUERDO 	 PC0 		//define PC0 com o nome de BOTAOESQUERDO
#define BOTAODIREITO 	 PC1		//define PC1 com o nome de BOTAODIREITO
#define D0		 PB3		//define PB3 com o nome de D0
#define D1		 PB4		//define PB4 com o nome de D1
#define D2		 PB5		//define PB5 com o nome de D2

#define TOP 39999         //valor para a máxima contagem

// Variável gravada na memória flash
const unsigned char Tabela[] PROGMEM = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78, 0x00, 0x18, 0x08, 0x03, 0x46, 0x21, 0x06, 0x0E};

void setup() {
}

void loop()
{
	// Variáveis para armazenar o tempo em que o botão foi pressionado
   unsigned long botaoEsquerdo = millis();
	unsigned long botaoDireito = millis(); 

	int valor = 0;	// variável para armazenar o valor do contador
  	char d0=0,d1=0, d2=0; // variáveis para armazenar os valores dos dígitos do display
	
	DDRB = 0b11111100;			//PB0 e PB1 como pinos de entrada, os demais pinos como saída
	PORTB= 0b00000011;			//habilita o pull-up do PB0 e PB1		 
	DDRD = 0xFF;				//PORTD como saída para os displays
	PORTD= 0xFF;				//desliga o display
	UCSR0B = 0x00;				//PD0 e PD1 como I/O genérico
	DDRC = 0b11111100;			//Pino para os botões definidos como entrada
  	PORTC = 0b00000011;			//Habilita pull-pu de PC0 e PC1
   OCR1B = 100;
  
   ICR1 = TOP;           //configura o período do PWM (20 ms)
  
    // Configura o TC1 para o modo PWM rápido via ICR1, prescaler = 8
   TCCR1A = (1 << WGM11);
   TCCR1B = (1 << WGM13) | (1<<WGM12) | (1 << CS11);
  
   set_bit(TCCR1A,COM1B1);     // Ativa o PWM no OC1A, modo de comparação não-invertido
  
	while(1) 
	{
		if(!tst_bit(PINC, BOTAOESQUERDO) && (millis() - botaoEsquerdo) > debounceInterval)  
		{ // se o botão esquerdo for pressionado
			_delay_ms(2);

			if(valor == 0){
				valor = 0;	// Não deixa decrementar mais se o valor for igual a 0
			}

			else{
				valor = valor - 9;	// Caso contrário decrementa 9 graus
				botaoEsquerdo = millis();	// Recebe o tempo em que o botão foi apertado
			}
		}
      
		if(!tst_bit(PINC, BOTAODIREITO) && (millis() - botaoDireito) > debounceInterval) 
		{ // se o botão direito for pressionado
			_delay_ms(2);

			if(valor == 180){
				valor = 180;	// Não permite incrementar se o valor for igual a 180
			}

			else{				// Caso contrário permite incrementar o valor
				valor = valor + 9;
				botaoDireito = millis(); 
			}
		}
        
      // Calculos para mostrar o valor em graus no display
      d2 = (valor)/100; // Calcula o primeiro dígito do valor
      d1 = valor%100;  // Calcula o segundo dígito do valor
      d1 = d1/10; // Calcula o terceiro dígito do valor
      d0 = valor%10; // Calcula o quarto dígito do valor

      // Regra de três para determinar este valor: ICR1(TOP) = 20 ms, OCR1B (2000) = 1 ms)
      OCR1B = (((valor/45)+0.5)*2000);     // Calcula o valor do PWM para o valor do contador
      // Mostra no display o valor em graus.
		clr_bit(PORTB,D2); // desliga o display

	  	DISPLAY = pgm_read_byte(&Tabela[d0]); 
		set_bit(PORTB,D0); // habilita o display
		_delay_ms(2);

		clr_bit(PORTB,D0); // desliga o display
		DISPLAY = pgm_read_byte(&Tabela[d1]); 
		set_bit(PORTB,D1); // habilita o display
		_delay_ms(2);

		clr_bit(PORTB,D1); // desliga o display
		DISPLAY = pgm_read_byte(&Tabela[d2]); 
		set_bit(PORTB,D2); // habilita o display
		_delay_ms(2);

	} // Laço infinito
}