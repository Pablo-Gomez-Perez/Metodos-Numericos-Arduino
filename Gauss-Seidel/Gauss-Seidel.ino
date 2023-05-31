#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd_1(0x27, 16, 2);

float x1 = 0, x2 = 0, x3 = 0, k, x1n, x2n, x3n, e;

void setup() {
  lcd_1.begin(16, 2);
  lcd_1.init();
  lcd_1.backlight();
  pinMode(13, OUTPUT);
}

void loop() {

  lcd_1.clear();
  x1n = (4 + x2 - x3) / 8;
  x2n = (-3 - x1n + x3) / 5;
  x3n = (7 + x1n - x2n) / 6;

  e = sqrt(pow(x1n - x1, 2) + pow(x2n - x2, 2) + pow(x3n - x3, 2));

  lcd_1.setCursor(0, 0);
  lcd_1.print("X1");
  lcd_1.setCursor(3, 0);
  lcd_1.print(x1n);
  lcd_1.setCursor(8, 0);
  lcd_1.print("X2");
  lcd_1.setCursor(11, 0);
  lcd_1.print(x2n);
  lcd_1.setCursor(0, 1);
  lcd_1.print("X3");
  lcd_1.setCursor(3, 1);
  lcd_1.print(x3n);
  lcd_1.setCursor(8, 1);
  lcd_1.print("E");
  lcd_1.setCursor(10, 1);
  lcd_1.print(e);

  if (e < 0.01) {
    digitalWrite(13, HIGH);
    while (true) {
    }
  } else {
    digitalWrite(13, LOW);
    x1 = x1n;
    x2 = x2n;
    x3 = x3n;
  }
  delay(1000);
}
