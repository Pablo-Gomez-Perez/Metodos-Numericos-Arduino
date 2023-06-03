#include <LiquidCrystal_I2C.h>
#include <math.h>
#include <Wire.h>

LiquidCrystal_I2C lcd_1(0x27, 16, 2);

float a = 1;  //limite inferior
float fa;
float c;   //punto medio
float ca;  //punto medio anterior
float fc;
float b = 3;  //limite superior
float fb;
float e;  //error
int i = 0;

void setup() {
  // put your setup code here, to run once:

  lcd_1.init();
  lcd_1.backlight();
  lcd_1.clear();
  pinMode(13, OUTPUT);
}

void loop() {

  fa = exp(a) + pow(a, 2) - 3 * a - 4;
  fb = exp(b) + pow(b, 2) - 3 * b - 4;
  c = (a + b) / 2;

  if (i > 0) {
    e = 100 * abs((c - ca) / c);
    lcd_1.clear();

    lcd_1.setCursor(0, 0);
    lcd_1.print("raiz");
    lcd_1.setCursor(5, 0);
    lcd_1.print(c);


    lcd_1.setCursor(0, 1);
    lcd_1.print("error");
    lcd_1.setCursor(6, 1);
    lcd_1.print(e);

    delay(1000);
  }

  if (e < 0.2) {
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);
  }
  ca = c;
  fc = exp(c) + pow(c, 2) - 3 * c - 4;
  if (fc * fa < 0) {
    b = c;
  } else {
    a = c;
  
  }

  i++;
}

float calcularPuntoMedio(float a, float b) {
  return (a + b) / 2;
}