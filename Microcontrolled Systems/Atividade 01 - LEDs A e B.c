void setup()
{
  //pinMode(LED_BUILTIN, OUTPUT);
  DDRB = 0b00110000;
  //DDRB = 1<<5;
  //DDRB = 1<<PB5;
  //DDRB = 32;
  //DDRB = 0x20;
  DDRB |= 1<<PB2;
}

void loop()
{
  PORTB = 0b00000000;
  PORTB = 0b00100000;
  delay(50);
  PORTB = 0b00010000;
  delay(50);
  PORTB = 0b00000000;
  delay(450);
}