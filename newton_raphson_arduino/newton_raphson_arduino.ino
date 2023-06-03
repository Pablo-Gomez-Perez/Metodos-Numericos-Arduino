#include <LiquidCrystal_I2C.h>
#include <math.h>
#include <Wire.h>

LiquidCrystal_I2C lcd_1(0x27, 16, 2);

  float fx;
  float f1x;
  float x1;
  float x0 = 4;
  float e;
  float ca = 0;
  int i = 0;
  int d = 1;

void setup() {
  // put your setup code here, to run once:

  lcd_1.init();
  lcd_1.backlight();
  lcd_1.clear();
  pinMode(13, OUTPUT);
}

void loop() {

  fx = exp(x0) + pow(x0, 2) - 3 * x0 - 4;
  f1x = exp(x0) + 2 * x0 - 3;
  x1 = x0 - (fx / f1x);

  if (i >= 0) {
    e = 100 * abs((x1 - ca) / x1);

    lcd_1.clear();

    lcd_1.setCursor(0, 0);
    lcd_1.print("raiz");
    lcd_1.setCursor(5, 0);
    lcd_1.print(x1);

    lcd_1.setCursor(0, 1);
    lcd_1.print("error");
    lcd_1.setCursor(6, 1);
    lcd_1.print(e);

    lcd_1.setCursor(10, 0);
    lcd_1.print("i=");
    lcd_1.setCursor(12, 0);
    lcd_1.print(d);
    delay(1000);
  }

  if (e < 0.2) {
    digitalWrite(13, HIGH);
    delay(500);

  } else {
    d++;
    digitalWrite(13, LOW);
  }

  ca = x1;
  x0 = x1;
  i++;
}

float calcularPuntoMedio(float a, float b) {
  return (a + b) / 2;
}