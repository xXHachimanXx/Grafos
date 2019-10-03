#include <stdio.h>
#include <iostream>
#include "../includes/Grafo.h"
using namespace std;

/**
 * Método para inicializar a matriz de adjascência.
 */
void Grafo::Grafo(int vertices, int arestas)
{
    this->vertices = vertices;
    this->arestas = arestas;
    this->matriz = new char*[vertices];

    for(int y = 0; y < vertices; y++)
    {
        this->matriz[y] = new char[y];
    }//end for

    init();
}

void Grafo::init()
{
    if(matriz != NULL)
    {
        for(int x = 0; x < numVertices; x++)
            for(int y = 0; y < numVertices; y++)
                this->matriz[x][y] = 0;
    }
}

/**
 * Destrutor
 */
Grafo::~Grafo()
{
    for(int y = 0; y < numVertices; y++)
    {
        delete matriz[y];
    }
    delete matriz;
}
