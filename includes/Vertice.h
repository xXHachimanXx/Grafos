#include <stdio.h>
#include <iostream>
#include <string>
#include "Grafo.h"
using namespace std;

//Usar fórmula de distância entre dois pontos
class Vertice
{
    public:
        // ----------------- Atributos
        /**
         * Coordenadas do grafo no plano.
         */
        int x, y; 

        // ----------------- Construtores
        Vertice();
        Vertice(int x, int y);
        
        // ----------------- Métodos
        void mostrarVertice();
};