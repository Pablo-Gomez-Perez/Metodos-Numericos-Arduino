#include <LiquidCrystal_I2C.h>
#include <math.h>
#include <Wire.h>

LiquidCrystal_I2C lcd_1(0x27, 16, 2);

float X0 = 3, X1 = 4, X2, fX0, fX1, e;

void setup() {
  // put your setup code here, to run once:

  lcd_1.init();
  lcd_1.backlight();
  lcd_1.clear();
}

void loop() {

  fX0 = exp(X0) + pow(X0, 2) - 3 * X0 - 4;
  fX1 = exp(X1) + pow(X1, 2) - 3 * X1 - 4;
  X2 = X1 - ((fX1 * (X0 - X1)) / (fX0 - fX1));
  e = 100 * abs((X2 - X1) / X2);

  lcd_1.clear();
  lcd_1.setCursor(0, 0);
  lcd_1.print("Raiz=");
  lcd_1.setCursor(5, 0);
  lcd_1.print(X2);

  lcd_1.setCursor(0, 1);
  lcd_1.print("Error=");
  lcd_1.setCursor(6, 1);
  lcd_1.print(e);
  if (e < 0.2) {
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);
    X0 = X1;
    X1 = X2;
  }
  delay(1000);
}
