package com.metnum.app.principal;

import com.metnum.app.classes.Biseccion;

/**
 * *************************************************************
 *  programa para hayar las raicen de una función algebraica o
 *  trascendental mediante el algoritmo de la biscección
 * *************************************************************
 *  realizado por: {@autor Pablo_G}
 * *************************************************************
 *
 * clase principal de arranque del programa
 *
 */
public class Main {

    public static void main(String[] args) {

        float limiteInferior = 1;
        float limiteSuperior = 3;
        
        Biseccion.evalua(limiteInferior, limiteSuperior);

    }
}
