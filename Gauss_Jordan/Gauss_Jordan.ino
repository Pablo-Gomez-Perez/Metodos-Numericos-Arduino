#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
const int N = 3;  // Número de ecuaciones y variables

float A[N][N + 1] = { { -1, 5, 4, 7 },
                      { 7, -3, -2, -4 },
                      { 1, 2, -1, 5 } };  // Matriz aumentada del sistema

void setup() {
  lcd.init();
  lcd.backlight();
  pinMode(13, OUTPUT);
}

void loop() {
  lcd.begin(16, 2);
  pinMode(13, OUTPUT);
  for (int i = 0; i < N; i++) {
    // Dividir la fila i por A[i][i]
    float divisor = A[i][i];
    for (int j = 0; j < N + 1; j++) {
      A[i][j] /= divisor;
    }

    // Hacer ceros en las columnas debajo de A[i][i]
    for (int k = 0; k < N; k++) {
      if (k != i) {
        float factor = A[k][i];
        for (int j = 0; j < N + 1; j++) {
          A[k][j] -= factor * A[i][j];
        }
      }
    }
  }




  digitalWrite(13, HIGH);
  lcd.clear();

  // Imprimir la solución del sistem
  lcd.setCursor(0, 0);
  lcd.print("x1= ");
  lcd.setCursor(3, 0);
  lcd.print(A[0][N]);

  lcd.setCursor(9, 0);
  lcd.print("x2= ");
  lcd.setCursor(12, 0);
  lcd.print(A[1][N]);

  lcd.setCursor(0, 1);
  lcd.print("x3= ");
  lcd.setCursor(3, 1);
  lcd.print(A[2][N]);


  // Esperar un tiempo antes de volver a calcular
  delay(1000);
}
