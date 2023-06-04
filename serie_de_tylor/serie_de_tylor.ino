#include <LiquidCrystal_I2C.h> 
#include <math.h>
#include <Wire.h>

LiquidCrystal_I2C lcd_1(0x27, 16, 2);

void setup() {
  lcd_1.init();
  lcd_1.backlight();
  lcd_1.clear();
}

void loop() {

  t = analogRead(A0);
  t = map(t, 0, 1023, 1, 3);
  Vr = 3 * pow(x, 2) + 2 * x - 1;
  fa = 3 * pow(a, 2) + 2 * a - 1;
  f1a = 6 * a + 2;
  f2a = 6;
  switch (t) {
    case 1:
      Va = fa;
      Ea = abs(Vr - Va);
      break;
    case 2:
      Va = fa + f1a * (x - a);
      Ea = abs(Vr - Va);
      break;
    case 3:
      Va = fa + f1a * (x - a) + f2a * (x - a) * (x - a) / 2;
      Ea = abs(Vr - Va);
      break;
  }

  lcd_1.setCursor(0, 0);
  lcd_1.print("Vr=");
  lcd_1.setCursor(3, 0);
  lcd_1.print(Vr);
  delay(1000);

  lcd_1.setCursor(0, 1);
  lcd_1.print("Va=");
  lcd_1.setCursor(3, 1);
  lcd_1.print(Va);

  lcd_1.setCursor(8, 0);
  lcd_1.print("Ea=");
  lcd_1.setCursor(11, 0);
  lcd_1.print(Ea);

  lcd_1.setCursor(8, 1);
  lcd_1.print("t=");
  lcd_1.setCursor(10, 1);
  lcd_1.print(t);

  delay(1000);

}