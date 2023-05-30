#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.begin(16, 2);
  lcd.init();
  lcd.backlight();
  pinMode(13, OUTPUT);
}

void loop() {
  lcd.clear();
  float matriz[3][4] = { { -1, 4, -1, 4 },
                         { -2, 4, 3, 14 },
                         { 1, 7, 4, 3 } };

  // Realizar operaciones elementales de fila
  for (int i = 0; i < 3; i++) {
    // Si el elemento diagonal es cero, intercambiar filas
    if (matriz[i][i] == 0) {
      for (int j = i + 1; j < 3; j++) {
        if (matriz[j][i] != 0) {
          // Intercambiar filas i y j
          for (int k = 0; k < 4; k++) {
            float temp = matriz[i][k];
            matriz[i][k] = matriz[j][k];
            matriz[j][k] = temp;
          }
          break;
        }
      }
    }

    // Hacer ceros debajo de la diagonal principal
    for (int j = i + 1; j < 3; j++) {
      float factor = matriz[j][i] / matriz[i][i];
      for (int k = i; k < 4; k++) {
        matriz[j][k] = matriz[j][k] - factor * matriz[i][k];
      }
    }
  }

  // Resolver el sistema usando eliminación hacia atrás
  float z = matriz[2][3] / matriz[2][2];
  float y = (matriz[1][3] - matriz[1][2] * z) / matriz[1][1];
  float x = (matriz[0][3] - matriz[0][1] * y - matriz[0][2] * z) / matriz[0][0];

  // Imprimir las soluciones en la pantalla LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("x=");
  lcd.print(x);
  lcd.setCursor(0, 1);
  lcd.print("y=");
  lcd.print(y);
  lcd.setCursor(8, 1);
  lcd.print("z=");
  lcd.print(z);

  delay(5000);  // Esperar 5 segundos antes de imprimir de nuevo
}
