#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <math.h>

LiquidCrystal_I2C lcd_1(0x27, 16, 2);

//prototipados de las funciones
float funcionDeX(float x);
int metodoUtlizar();
int particionDeN();
float metodoDelTrapecio(int n);
//=============================

float resultadoT;  //almacena el valor del resultado obtenido por el metodo del trapecio
float resultadoS;  //almacena el valor del resultado obtenido por el metodo de Simpson
int metodo = 0;
int particiones = 0;

void setup() {
  lcd_1.init();
  lcd_1.begin(16, 2);
  lcd_1.backlight();
  Serial.begin(9600);
}

void loop() {

  metodo = metodoUtlizar();
  particiones = particionDeN();

  Serial.print(metodo);
  Serial.print("\n");
  lcd_1.clear();

  switch (metodo) {
    case 1:
      resultadoT = metodoDelTrapecio(particiones);
      lcd_1.setCursor(0, 0);
      lcd_1.print("Trapecio:");
      lcd_1.print(resultadoT);
      lcd_1.setCursor(0, 1);
      lcd_1.print("p=");
      lcd_1.print(particiones);
      Serial.print(resultadoT); 
      Serial.print("\n");
      Serial.print(particiones);
      break;
    case 2:
      resultadoS = metodoDeSimpson(particiones);
      lcd_1.setCursor(0, 0);
      lcd_1.print("Simpson: ");
      lcd_1.print(resultadoS);
      lcd_1.setCursor(0, 1);
      lcd_1.print("p=");
      lcd_1.print(particiones);
      Serial.print(resultadoS);
      Serial.print("\n");
      Serial.print(particiones);
      break;
    default:
      lcd_1.setCursor(0, 0);
      lcd_1.print("NULL:  Value");
      lcd_1.setCursor(1, 0);
      lcd_1.print("potenciometer");
      break;
  }

  delay(1000);
}

/**
 * metodo que retorna el valor de la función evaluado en X
 */
float funcionDeX(float x) {
  return (pow(x, 2) + 3 * x + 1) * exp(3 * x);
}

/**
 * metodo a utilizar con el potenciometro conectado al puerto analogico
 * A0 del arduino
 * @return 0 a 1
 */
int metodoUtlizar() {
  int m = analogRead(A0);
  return map(m, 0, 1023, 1, 3);
}

/**
 * Metodo a utilizar con un potenciometro conectado al puerto analógico @code{A1}
 * del arduino, con el cual se leeran las particiones de n utilizadas por cualquier
 * de los metodos para resolver la integral de forma numerica
 * @return{valores de 1 a 20} para 20 particiones de N
 */
int particionDeN() {
  int n = analogRead(A1);
  return map(n, 0, 1023, 1, 21);
}

/**
 * metodo para resolver integrales mediante el metodo del trapecio
 * usando n como la cantidad propuesta para las particiones
 * del procedimiento
 */
float metodoDelTrapecio(int n) {
  float a = 0.0;
  float b = 2.0;
  float h = (b - a) / n;
  float s = funcionDeX(a) + funcionDeX(b);

  for (int i = 1; i < n; i++) {
    s += 2 * funcionDeX(a + i * h);
  }

  return (h / 2) * s;
}

/**
 * metodo para resolver integrales mediante el método de Simpson
 * usando @param{n} como la cantidad propuesta para las particiones
 * del procedimiento
 */
float metodoDeSimpson(int n) {
  float a = 0.0;  //limite de evaluación inferior
  float b = 2.0;  //metodo de evaluacion superior
  float h = (b - a) / n;
  float x, sum = 0.0;

  for (int i = 0; i <= n; i++) {
    x = a + i * h;
    if (i == 0 || i == n) {
      sum += funcionDeX(x);
    } else if (i % 2 != 0) {
      sum += 4 * funcionDeX(x);
    } else {
      sum += 2 * funcionDeX(x);
    }
  }
  return (h / 3) * sum;
}
