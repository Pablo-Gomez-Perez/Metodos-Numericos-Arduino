#include <LiquidCrystal_I2C.h>
#include <math.h>
#include <Wire.h>

LiquidCrystal_I2C lcd_1(0x27, 16, 2);

float funcionEvaluada(float a);
float funcionDerivada(float a);

float v1 = 1;
float xi;
float xi_siguiente;
float funcion_x;
float funcion_derivada;
int i = 0;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  lcd_1.init();
  lcd_1.backlight();
  lcd_1.clear();
  pinMode(13, OUTPUT);
}

void loop() {

  lcd_1.clear();

  if (i < 0) {

    lcd_1.setCursor(0, 0);
    lcd_1.print("xi=");
    lcd_1.setCursor(5, 0);
    lcd_1.print(xi);

    xi_siguiente = funcionEvaluada(v1)
  }



  i++;
}

float funcionEvaluada(float a) {
  return pow(a, 5) - a - 1;
}

float funcionDerivada(float a) {
  return 5 * pow(a, 4) - 1;
}