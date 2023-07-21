#include "LCD.h" // LCD

// Botoes
#define debounceInterval  1 //ms
unsigned int debounceTimeA = 0;
unsigned int debounceTimeD = 0;
unsigned int debounceTimeE = 0;

int lastStateAumenta = 1; // ultima leitura com ruido
int botaoAumenta = 1; // estado do botao

int lastStateDiminui = 1; // ultima leitura com ruido
int botaoDiminui = 1; // estado do botao

int lastStateEnter = 1; // ultima leitura com ruido
int botaoEnter = 1; // estado do botao

int flagState = 0; // fase da config
int flagDecrease = 0; // fase da config

#define TOP PC5
#define DOWN PC3
#define RIGHT PC4
#define LEFT PC2

char T0, T1, T2, T3;

// temperature related
#define MAX_TEMP  212.f
#define MIN_TEMP  11.f
#define MAX_COUNT 1011
#define MIN_COUNT 79
//212 1011
//190 912
//160 771
//138 670
//120 585
//29 154
//11 79

unsigned int adc_res; // temperatura

// --------------------
//Variables
float temperature_read = 0.0;

#define num_ADC_average 32
volatile unsigned int adc_result0[num_ADC_average]; // average 32 conversions channel 0
volatile unsigned int adc_pos0 = num_ADC_average-1; // current ADC value for channel 0

volatile unsigned long my_millis = 0;

#define MOTORON   PORTD |= 1<<PD3
#define MOTOROFF  PORTD &= ~(1<<PD3)

#define HEATON   PORTD |= 1<<PD2
#define HEATOFF  PORTD &= ~(1<<PD2)

#define BUZZON   PORTC |= 1<<PC1
#define BUZZOFF  PORTC &= ~(1<<PC1)
#define BUZZCOM PORTC ^= (1<<PC1)

#define COUNT2TEMP(c)  (MIN_TEMP+(((MAX_TEMP-MIN_TEMP)/(MAX_COUNT-MIN_COUNT))*(((float)(c))-MIN_COUNT)))

volatile unsigned int beep_period;

#define BEEP()  beep_period = 200

int main() {
  //void setup() {
  // disable interrupts
  cli();

  MOTOROFF;
  HEATOFF;
  BUZZON;
  
  ADMUX = 0; // ADC0, AREF
  ADCSRA = 1<<ADEN|1<<ADIE;
  ADCSRA |= 1<<ADPS2|1<<ADPS1|1<<ADPS0; // 128 ADC prescaler / 9615 conversions/second
  ADCSRB = 0;
  DIDR0 = 1<<ADC0D; // disable digital input on A0

  // configuracao timer3
  // use mode 0 normal
  TCCR1A = 0;
  TCCR1B = (1<<CS11); // clkio/8 prescaler
  TCCR1C = 0;
  OCR1A = 0x07CF; //1999 that counts 2000 = 1ms
  TIMSK1 = 1<< OCIE1A; // output compare unit A

  DDRD = 0xFF; // LCD e Motor e Resistencia
  DDRB = 1<<PB0|1<<PB1; // LCD
  DDRC = 1<<PC1; // BUZZER

  PORTB = (1<<PB5) | (1<<PB4) | (1<<PB3); // pull-up botoes

  // enable interrupts
  sei();

  Serial.begin(115200);

  ADCSRA |= 1<<ADSC; // start ADC conversion

  inic_LCD_4bits();

  BEEP();

  volatile long tempoSovar = 1*60000;
  volatile long tempoDescanso = 1*60000;
  volatile long tempoAssar = 1*60000;
  volatile long tempoDisplay = 0;

  while(1) {

    cmd_LCD(0x80,0); // Primeiro endereço do LCD

    // Intrução de escrita dos caracteres.
    if(flagState == 0) {
      T3 = ((tempoSovar%60000)/1000)%10; // Tempo em unidade de segundo;
      T2 = ((tempoSovar%60000)/1000)/10; // Tempo em dezena de segundo;
      T1 = (tempoSovar/60000)%10; // Tempo em unidade de minuto;
      T0 = (tempoSovar/60000)/10; // Tempo em dezena de minuto;

      cmd_LCD('S',1);
      cmd_LCD('O',1);
      cmd_LCD('V',1);
      cmd_LCD('A',1);
      cmd_LCD('R',1);
      cmd_LCD(' ',1);

      cmd_LCD(T0+'0',1);
      cmd_LCD(T1+'0',1);
      cmd_LCD(':',1);
      cmd_LCD(T2+'0',1);
      cmd_LCD(T3+'0',1);
    }

    if(flagState == 1) {
      T3 = ((tempoDescanso%60000)/1000)%10; // Tempo em unidade de segundo;
      T2 = ((tempoDescanso%60000)/1000)/10; // Tempo em dezena de segundo;
      T1 = (tempoDescanso/60000)%10; // Tempo em unidade de minuto;
      T0 = (tempoDescanso/60000)/10; // Tempo em dezena de minuto;

      cmd_LCD('D',1);
      cmd_LCD('E',1);
      cmd_LCD('S',1);
      cmd_LCD('C',1);
      cmd_LCD('A',1);
      cmd_LCD('N',1);
      cmd_LCD('S',1);
      cmd_LCD('O',1);
      cmd_LCD(' ',1);

      cmd_LCD(T0+'0',1);
      cmd_LCD(T1+'0',1);
      cmd_LCD(':',1);
      cmd_LCD(T2+'0',1);
      cmd_LCD(T3+'0',1);
    }

    if(flagState == 2) {
      T3 = ((tempoAssar%60000)/1000)%10; // Tempo em unidade de segundo;
      T2 = ((tempoAssar%60000)/1000)/10; // Tempo em dezena de segundo;
      T1 = (tempoAssar/60000)%10; // Tempo em unidade de minuto;
      T0 = (tempoAssar/60000)/10; // Tempo em dezena de minuto;

      cmd_LCD('A',1);
      cmd_LCD('S',1);
      cmd_LCD('S',1);
      cmd_LCD('A',1);
      cmd_LCD('R',1);
      cmd_LCD(' ',1);

      cmd_LCD(T0+'0',1);
      cmd_LCD(T1+'0',1);
      cmd_LCD(':',1);
      cmd_LCD(T2+'0',1);
      cmd_LCD(T3+'0',1);
    }

    int leitura = (PINC & (1<<RIGHT));
    if (leitura != lastStateAumenta) {
      debounceTimeA = my_millis;
    }
  
    if ((my_millis - debounceTimeA) > debounceInterval) {
      if (botaoAumenta != leitura) {
        botaoAumenta = leitura;
        if (botaoAumenta == 0) {
          if((flagState == 0) && (tempoSovar < (60*60000))) {
            tempoSovar = tempoSovar + 1*60000;
          }
          if((flagState == 1) && (tempoDescanso < (100*60000))) {
            tempoDescanso = tempoDescanso + 1*60000;
          }
          if((flagState == 2) && (tempoAssar < (120*60000))) {
            tempoAssar = tempoAssar + 1*60000;
          }
        }
      }
    }
    lastStateAumenta = leitura;

    leitura = (PINC & (1<<LEFT));
    if (leitura != lastStateDiminui) {
      debounceTimeD = my_millis;
    }
  
    if ((my_millis - debounceTimeD) > debounceInterval) {
      if (botaoDiminui != leitura) {
        botaoDiminui = leitura;
        if (botaoDiminui == 0) {
          if((flagState == 0) && (tempoSovar > 0)) {
            tempoSovar = tempoSovar - 1*60000;
          }
          if((flagState == 1) && (tempoDescanso > 0)) {
            tempoDescanso = tempoDescanso - 1*60000;
          }
          if((flagState == 2) && (tempoAssar > 0)) {
            tempoAssar = tempoAssar - 1*60000;
          }
        }
      }
    }
    lastStateDiminui = leitura;

    leitura = (PINC & (1<<TOP));
    if (leitura != lastStateEnter) {
      debounceTimeE = my_millis;
    }
  
    if ((my_millis - debounceTimeE) > debounceInterval) {
      if (botaoEnter != leitura) {
        botaoEnter = leitura;
        if (botaoEnter == 0) {
          if(flagState == 0) {
            flagState = 1;
            cmd_LCD(0x01,0);
          }
          else if(flagState == 1) {
            flagState = 2;
            cmd_LCD(0x01,0);
          }
          else if(flagState == 2) {
            flagState = 3;
            cmd_LCD(0x01,0);
          }
        }
      }
    }
    lastStateEnter = leitura;

    if(flagState == 3) {
      tempoDisplay = tempoSovar;
      tempoSovar += my_millis;
      
      while(my_millis <= tempoSovar) {
        MOTORON;
      }
      cmd_LCD(0x01,0);
      MOTOROFF;
      BEEP();

      tempoDisplay = tempoDescanso;
      tempoDescanso += my_millis;
      while(my_millis <= tempoDescanso) {
        MOTOROFF;
        HEATOFF;
      }
      cmd_LCD(0x01,0);
      BEEP();

      tempoDisplay = tempoAssar;
      tempoAssar += my_millis;
      while(my_millis <= tempoAssar) {
        HEATON;
      }
      cmd_LCD(0x01,0);
      HEATOFF;
      BEEP();
      flagState = 4;
    }

    if(flagState == 4) {
      cmd_LCD('F',1);
      cmd_LCD('I',1);
      cmd_LCD('N',1);
      cmd_LCD('A',1);
      cmd_LCD('L',1);
      cmd_LCD('I',1);
      cmd_LCD('Z',1);
      cmd_LCD('A',1);
      cmd_LCD('D',1);
      cmd_LCD('O',1);
      cmd_LCD(' ',1);
    }
   
    if (my_millis%1000==0) {
      Serial.print(flagState);
      Serial.print(", ADC0: ");
      adc_res = 0;
      for (int i=0; i<num_ADC_average; i++)
        adc_res += adc_result0[i];
      adc_res /= num_ADC_average;
      Serial.print(adc_res);
      Serial.print(", ");

      temperature_read = COUNT2TEMP(adc_res);
      unsigned char digitos[tam_vetor];
      ident_num(temperature_read,digitos);
      Serial.print(temperature_read);
      Serial.println();
      cmd_LCD(0x8D,0);      //desloca o cursor para que os 3 digitos fiquem a direita do LCD
      cmd_LCD(digitos[2],1);
      cmd_LCD(digitos[1],1);
      cmd_LCD(digitos[0],1);
    }
    
  }//while 1

  return 0;
}

ISR (ADC_vect)
{
  adc_result0[adc_pos0++%num_ADC_average] = ADC;
  ADCSRA |= 1<<ADSC; // start new ADC conversion  
}

ISR(TIMER1_COMPA_vect)
{
  OCR1A += 0x07CF;
  my_millis += 1;

  if (beep_period > 0) {
    beep_period--;
    BUZZCOM;
  }
}
