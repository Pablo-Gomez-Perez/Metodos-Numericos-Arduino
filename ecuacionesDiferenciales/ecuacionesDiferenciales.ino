#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd_1(0x27, 16, 2);

//==============prototipos de las funciones a utilizar============
int seleccionarMetodo();
int particionDeN();
float funcionEvaluadaEn(float x, float y);
float deltaX(float inicial, float final, int particion);
float xEnN(int n, float incremento);
float metodoDeEuler(int particiones);
float metodoDeKutta(int particiones);
float _k2_(float x, float y, float delta, float _k1);
float _K3_(float x, float y, float delta, float _k2);
float _K4_(float x, float y, float delta, float _k3);
//================================================================

float x_inicial = 1;  //valor inicial para los calculos
float x_final = 1.2;  //valor final en la evaluacion
float y_inicial = 5;
int particiones;

void setup() {
  lcd_1.init();
  lcd_1.backlight();
  lcd_1.begin(16, 2);
}

void loop() {

  lcd_1.clear();
  particiones = particionDeN();  //se indican las particiones de N

  switch (seleccionarMetodo()) {
    case 1:

      lcd_1.setCursor(0, 0);
      lcd_1.print("Euler");
      lcd_1.setCursor(6, 0);
      lcd_1.print("n=");
      lcd_1.setCursor(8, 0);
      lcd_1.print(particionDeN());
      lcd_1.setCursor(10, 0);
      lcd_1.print("h=");
      lcd_1.setCursor(12, 0);
      lcd_1.print(deltaX(x_inicial, x_final, particiones));
      lcd_1.setCursor(0, 1);
      lcd_1.print("X=");
      lcd_1.setCursor(2, 1);
      lcd_1.print(x_final);
      lcd_1.setCursor(7, 1);
      lcd_1.print("Y=");
      lcd_1.setCursor(9, 1);
      lcd_1.print(metodoDeEuler(particiones));

      break;

    case 2:
      lcd_1.setCursor(0, 0);
      lcd_1.print("Kutta");
      lcd_1.setCursor(6, 0);
      lcd_1.print("n=");
      lcd_1.setCursor(8, 0);
      lcd_1.print(particionDeN());
      lcd_1.setCursor(10, 0);
      lcd_1.print("h=");
      lcd_1.setCursor(12, 0);
      lcd_1.print(deltaX(x_inicial, x_final, particiones));
      lcd_1.setCursor(0, 1);
      lcd_1.print("X=");
      lcd_1.setCursor(2, 1);
      lcd_1.print(x_final);
      lcd_1.setCursor(7, 1);
      lcd_1.print("Y=");
      lcd_1.setCursor(9, 1);
      lcd_1.print(metodoDeKutta(particiones));
      break;

    default:
      lcd_1.setCursor(0, 0);
      lcd_1.print("Null Method");
      break;
  }

  delay(1000);
}



/*
/**
 * toma la lectura de un potenciometro conectado al puerto anlogico A0 del arduino
 * y los valores retornados serán usados para seleccionar el método a utilizar para
 * la solución
 */
int seleccionarMetodo() {
  int n = analogRead(A0);
  return map(n, 0, 1023, 1, 3);
}

/**
 * lee un potenciometro conectado al puerto analógico A0
 * y retorna la cantidad de particiones de n a evaluar
 */
int particionDeN() {
  int n = analogRead(A1);
  return map(n, 0, 1023, 0, 21);
}

/**
 * @return la función evaluada en los puntos pasados como parametros
 */
float funcionEvaluadaEn(float x, float y) {
  return 2 * x - 3 * y + 1;
}

/**
 * calcula el valor de los incrementos de x
 * @return deltaX
 */
float deltaX(float inicial, float final, int particion) {
  return (final - inicial) / particion;
}

/**
 * calcula el valor de la y´ mediante el método de euler haciendo uso de n
 * particiones
 */
float metodoDeEuler(int particiones) {
  float y = y_inicial;
  float x = x_inicial;
  float delta = deltaX(x_inicial, x_final, particiones);
  float xAux;
  float yAux;
  for (int i = 0; i < particiones; i++) {
    xAux = x_inicial + i * delta;
    yAux = y + delta * funcionEvaluadaEn(x, y);
    x = xAux;
    y = yAux;
  }
  return y;
}

/**
 * Un miembro de la familia de los métodos Runge-Kutta usado ampliamente es el de cuarto orden.
 * Es usado tanto que a menudo es referenciado como «RK4» o como «el método Runge-Kutta».
 * proporciona un pequeño margen de error con respecto a la solución real del problema.
 * se utiliza para resolver ecuaciones diferenciales.
 * @param particiones cantidad de iteraciones a realizar, tambien utilizado para el calculo de *delta*
 * @return Y+1;
 */
float metodoDeKutta(int particiones) {
  float x = x_inicial;
  float y = y_inicial;
  float delta = deltaX(x_inicial, x_final, particiones);
  float k1;
  float k2;
  float k3;
  float k4;
  float pendiente;

  for (int i = 0; i < particiones; i++) {
    k1 = funcionEvaluadaEn(x, y);
    k2 = _K2_(x, y, delta, k1);
    k3 = _K3_(x, y, delta, k2);
    k4 = _K4_(x, y, delta, k3);
    pendiente = y + ((k1 + (2 * k2) + (2 * k3) + k4) * delta) / 6;
    y = pendiente;
    x = x + delta;
  }
  return pendiente; 
}

/**
 * función que calcula el segundo paso para el método de runge kutta
 * @param x
 * @param y
 * @param delta el incremento o intervalos de evalución para cada una de las iteraciones
 */
float _K2_(float x, float y, float delta, float _k1) {
  return funcionEvaluadaEn(x + (delta / 2), y + (delta / 2) * _k1);
}

/**
 * función que calcula el tercer paso para el método de runge kutta
 * @param x
 * @param y
 * @param delta el incremento o intervalos de evalución para cada una de las iteraciones
 */
float _K3_(float x, float y, float delta, float _k2) {
  return funcionEvaluadaEn(x + (delta / 2), y + (delta / 2) * _k2);
}

/**
 * función que calcula el cuarto paso para el método de runge kutta
 * @param x
 * @param y
 * @param delta el incremento o intervalos de evalución para cada una de las iteraciones
 */
float _K4_(float x, float y, float delta, float _k3) {
  return funcionEvaluadaEn(x + delta, y + delta * _k3);
}
