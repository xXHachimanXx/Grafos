#include <stdio.h>
#include <iostream>
#include <string>
#include "../../includes/Grafo.h"
using namespace std;

/**
 * Classe para criar vértices com coordenadas (x, y) no plano.
 */
class Vertice
{
    public:
        // ----------------- Atributos
        /**
         * Coordenadas do grafo no plano.
         */
        int x, y; 

        // ----------------- Construtores
        Vertice(){}
        Vertice(int x, int y) : x(x), y(y) {}
        
        // ----------------- Métodos
        void mostrarVertice()
        {   
            cout << "V(" << this->x << ',' << this->y << ')';
        }
};