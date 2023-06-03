#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd_1(0x27,16,2);

int terminoDeLaSerie;
int x; //función valuada en el punto x
int a; //valor propuesto para calculo de la aproximación
float valorAproximado;
float primerTermino;
float segundoTermino;
float tercerTermino;
float cuartoTermino;
float quintoTermino;

void setup() {
  // put your setup code here, to run once:
  lcd_1.init();
  lcd_1.backlight();
  lcd_1.clear();
  
}

void loop(){

  lcd_1.clear();

  terminoDeLaSerie = analogRead(A0);
  terminoDeLaSerie = map(terminoDeLaSerie, 0, 1023, 1, 6);

  x = analogRead(A1);
  x = map(x, 0, 1023, 1, 21);

  lcd_1.setCursor(0, 0);
  lcd_1.print("Tr=");
  lcd_1.setCursor(4, 0);
  lcd_1.print(terminoDeLaSerie);

  lcd_1.setCursor(8, 0);
  lcd_1.print("x=");
  lcd_1.setCursor(11, 0);
  lcd_1.print(x);

  lcd_1.setCursor(0, 1);

  switch (terminoDeLaSerie) {
    case 1:
      lcd_1.print("prim");
      break;
    
    case 2:
      lcd_1.print("segundo");
      break;

    case 3:
      lcd_1.print("tercero");
      break;

    case 4:
      lcd_1.print("cuarto");
      break;

    case 5:
      lcd_1.print("quinto");
      break;
  }

  delay(1000);

}