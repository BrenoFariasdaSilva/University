// 3. Utilizando o deslocamento de bits crie um programa em C que ligue 8 LEDs conforme a figura, da seguinte forma:

// a) Ligue sequencialmente 1 LED da direita para a esquerda (o LED deve permanecer ligado até que todos os 8 estejam ligados, depois eles devem ser desligados e o processo repetido).

void setup()
{
  DDRD = 0b11111111; //Atribui as portas como saída;
}

void loop()
{
  PORTD = 0b11111111; //Define as portas D mandando 1;
  for(int i=0; i<8; i++){ //I sendo usado para referenciar as portas (direita -> esquerda);
      PORTD &= ~(1 << i); //Deslocamento de bit 0 para a porta I (&= para atribuir 0 a porta);
    delay(300); 
  }
}


// b) Ligue sequencialmente 1 LED da esquerda para a direita, mesma lógica da letra ª
void setup()
{
  DDRD = 0b11111111; //Atribui as portas como saída;
}

void loop()
{
  PORTD = 0b11111111; //Define as portas D mandando 1;
  for(int i=7; i>=0; i--){ //I sendo usado para referenciar as portas; (Esquerda -> direita) (&= para atribuir 0 a porta);

      PORTD &= ~(1 << i); //Deslocamento de bit 0 para a porta I;
    delay(300);
  }
}


// c) Ligue sequencialmente 1 LED da direita para a esquerda, desta vez somente um LED deve ser ligado por vez.
void setup()
{
  DDRD = 0b11111111; //Atribui as portas como saída;
}

void loop()
{
  PORTD = 0b11111111; //Define as portas D mandando 1;
  for(int i=0; i<8; i++){ //I sendo usado para referenciar as portas; (Direita -> Esquerda)
      PORTD = ~(1 << i); // Atribuindo cada porta específica com 0 (ligado)
    delay(300);
  }
}


// d) Ligue sequencialmente 1 LED da esquerda para a direita e vice-versa (vai e volta), só um LED deve ser ligado por vez.
void setup()
{
  DDRD = 0b11111111; //Atribui as portas como saída;
}

void loop()
{
  PORTD = 0b11111111;  //Define as portas D mandando 1;
  for(int i=7; i>=0; i--){ //I sendo usado para referenciar as portas (esquerda -> direita);
      PORTD = ~(1 << i); // Atribuindo cada porta específica com 0 (ligado)
    delay(300);
  }
  for(int i=0; i<8; i++){ //I sendo usado para referenciar as portas (direita -> esquerda);
      PORTD = ~(1 << i); // Atribuindo cada porta específica com 0 (ligado)
    delay(300);
  }
}
