#define debounceInterval 50 // ms
#define offInterval 800     // ms
unsigned int debounceTime = 0;
unsigned int onTime = 0;
int lastState = 0;  // ultima leitura com ruido
int lastState2 = 0; // ultima leitura com ruido botão 2
int atual = 0;
int botao = 0;  // estado do botao
int botao2 = 0; // estado do botao 2

void setup()
{ // Leds como saida
  DDRD |= 0b10000000;
  DDRB |= 0b00000001;
  DDRC |= 0b00100000;
  PORTD |= 0b00001100; // Pull up
}

void loop()
{
  int leitura = PIND & (1 << PD2);
  int leitura2 = PIND & (1 << PD3);

  if (leitura != lastState || leitura2 != lastState2)
    debounceTime = millis();

  // Verifico se o estado do botão é igual ao estado anterior
  // Se for igual verifico se o tempo da ultima mudança de estado
  //(clique) é superior a 800ms
  if (botao2 == lastState2)
  {
    if ((millis() - onTime >= offInterval) && botao2 == 0)
    {
      PORTB &= ~(1 << PB0);
      PORTC &= ~(1 << PC5);
      PORTD &= ~(1 << PD7);
    }
  }
  if (botao == lastState)
  {
    if ((millis() - onTime >= offInterval) && botao == 0)
    {
      PORTB &= ~(1 << PB0);
      PORTC &= ~(1 << PC5);
      PORTD &= ~(1 << PD7);
    }
  }
  // Botão 1
  if ((millis() - debounceTime) > debounceInterval)
  {
    if (botao != leitura)
    {
      botao = leitura;
      if (botao == 0)
      {
        onTime = millis();
        if (atual == 0)
        {
          PORTC &= ~(1 << PC5);
          PORTB |= (1 << PB0);
          atual = 1;
        }
        else if (atual == 1)
        {
          PORTB &= ~(1 << PB0);
          PORTD |= (1 << PD7);
          atual = 2;
        }
        else if (atual == 2)
        {
          PORTD &= ~(1 << PD7);
          PORTC |= (1 << PC5);
          atual = 0;
        }
      }
    }
  }
  // Botão 2
  if ((millis() - debounceTime) > debounceInterval)
  {
    if (botao2 != leitura2)
    {
      botao2 = leitura2;
      if (botao2 == 0)
      {
        // Se o botão for clicado, salvo o tempo atual;
        onTime = millis();
        if (atual == 0)
        {
          PORTB &= ~(1 << PB0);
          PORTC |= (1 << PC5);
          atual = 2;
        }
        else if (atual == 1)
        {
          PORTD &= ~(1 << PD7);
          PORTB |= (1 << PB0);
          atual = 0;
        }
        else if (atual == 2)
        {
          PORTC &= ~(1 << PC5);
          PORTD |= (1 << PD7);
          atual = 1;
        }
      }
    }
  }
  lastState = leitura;
  lastState2 = leitura2;
}