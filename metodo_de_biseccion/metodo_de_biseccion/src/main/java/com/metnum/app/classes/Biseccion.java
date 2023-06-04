package com.metnum.app.classes;

public class Biseccion {

    /**
     * 
     * evalúa si el el intervalo inicial es solucín de la función, es decir
     * si dentro del rango {@code [LimiteInferior,LimiteSuperior]} se encuentra una
     * o mas raices de la función, para ello se deve evaluar la funcion en f(a) y
     * f(b)
     * y multiplicar los resultados, si el resultado es < 0 indica que en ese
     * intervalo
     * existe la solución de la función.
     * 
     * @param limiteInferior
     * @param limiteSuperior
     * @return
     */
    public static boolean esIntervaloSolucion(float limiteInferior, float limiteSuperior) {
        float[] valores = evaluaFuncionEnPunto(limiteInferior,0,limiteSuperior);
        boolean esSolucion = (valores[0] * valores[2]) < 0 ? true : false;
        return esSolucion;
    }

    /**
     * realiza el método iterativo hasta dar con la solución de la raiz de la
     * función
     * o el valor que mas se le eaproxime cuando el método tiende al infinito
     * 
     * @param limiteInferior
     * @param limiteSuperior
     */
    public static void esRaizEncontrada(float limiteInferior, float limiteSuperior) {

        float puntoMedio;
        float[] funcionEvaluada;       

        try{

            Thread.sleep(3000);

            puntoMedio = calcularPuntoMedio(limiteInferior, limiteSuperior);

            funcionEvaluada = evaluaFuncionEnPunto(limiteInferior, puntoMedio, limiteSuperior);

            

            if (funcionEvaluada[1] == 0 || (funcionEvaluada[0]*funcionEvaluada[1])==0) {

                System.out.println("\n==========================================");
                System.out.println("Solución encontrada");
                System.out.println("Valor: " + funcionEvaluada[1]);
                System.out.println("==========================================\n");
    
            } else if (funcionEvaluada[0] * funcionEvaluada[1] < 0) {
    
                System.out.println("\n==========================================");
                System.out.println("| cambio de intervalo: [" + limiteInferior + "," + puntoMedio + "]");
                System.out.println("==========================================");
                System.out.println("| f(Li) = " + funcionEvaluada[0]);
                System.out.println("| f(Ci) = " + funcionEvaluada[1]);
                System.out.println("| f(Ls) = " + funcionEvaluada[2]);
                System.out.println("==========================================\n");
                esRaizEncontrada(limiteInferior, puntoMedio);
    
            } else if(funcionEvaluada[0] * funcionEvaluada[1] > 0){
    
                System.out.println("\n==========================================");
                System.out.println("| cambio de intervalo: [" + puntoMedio + "," + limiteSuperior + "]");
                System.out.println("==========================================");
                System.out.println("| f(Li) = " + funcionEvaluada[0]);
                System.out.println("| f(Ci) = " + funcionEvaluada[1]);
                System.out.println("| f(Ls) = " + funcionEvaluada[2]);
                System.out.println("==========================================\n");
                esRaizEncontrada(puntoMedio, limiteSuperior);
    
            }

        }catch(Exception er){
            er.printStackTrace();
        }

    }

    /**
     * inicializa todo el proceso primero evalúa que en el intervalo inicial se
     * encuentr la
     * solución o raiz de la función con la que se está trabajando mediante el
     * método
     * {@code esIntervaloSolucion(float limiteInferior, float limiteSuperior)} si
     * retorna {@code true} se llama la función
     * {@code esRaizEncontrada(float limiteInferior, float limiteSuperior)}
     * la cual funciona de manera recursiva hasta dar con la solución, o se le
     * detiene en el numero de iteracines suficientes para saver el valor aproximado
     * 
     * @param limiteInferior
     * @param limiteSuperior
     */
    public static void evalua(float limiteInferior, float limiteSuperior) {
        if(!esIntervaloSolucion(limiteInferior, limiteSuperior)){
            System.out.println("\n==========================================");
            System.out.println("| No es intervalo solucion: [" + limiteInferior + "," + limiteSuperior + "]");
            System.out.println("==========================================\n");
            return;
        }

        esRaizEncontrada(limiteInferior, limiteSuperior);
    }

    /**
     * calcula el punto pedio del intervalo en el cual se está buscando la raiz de
     * la función
     * dividiendo el límite superior entre el límite inferior
     * 
     * @param a
     * @param b
     * @return
     */
    public static float calcularPuntoMedio(float a, float b) {
        return (a + b) / 2;
    }

    /**
     * evalúa la función en los tres puntos asignados a, b, c donde:
     * 
     * @param a es el limite inferior del intervalo
     * @param c es el punto medio del intervalo
     * @param b es el limite superior del intervalo
     * @return un vector con los tres valores de la función evaluada en esos puntos
     *         [a, b, c]
     */
    public static float[] evaluaFuncionEnPunto(float a, float c, float b) {

        float[] valores = {
                (float) (Math.pow(Math.E,a)+Math.pow(a, 2)-3*a-4), //función evaluada en a
                (float) (Math.pow(Math.E,c)+Math.pow(c, 2)-3*c-4), //funcion evaluada en c
                (float) (Math.pow(Math.E,b)+Math.pow(b, 2)-3*b-4)  //funcion evaluada en b
        };

        return valores;
    }



}