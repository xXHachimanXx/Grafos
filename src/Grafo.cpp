#include <stdio.h>
#include <iostream>
#include "../includes/Grafo.h"
using namespace std;

/**
 * Método para inicializar a matriz de adjascência.
 */
Grafo::Grafo(int vertices, int arestas)
{
    if(vertices >= 0 && arestas >= 0)
    {        
        this->vertices = vertices;
        this->arestas = arestas;
        this->matriz = new int*[vertices];

        for(int y = 0; y < vertices; y++)
        {
            this->matriz[y] = new int[y];
        }//end for

        init();
    }
    else
    {
        cout << "ERRO: Parâmetro(s) do grafo inválido(s)!";
    }//end if
}

/**
 * Método para registrar adjascência na matriz.
 */
void Grafo::conectarVertices(char v1, char v2)
{
    //transformar char em posicao na matriz
    int x = (int)v1 - 97;
    int y = (int)v2 - 97;    
    this->matriz[x][y] = 1;
}

/**
 * Inicializar todas as adjascências com '0'.
 */
void Grafo::init()
{
    if(matriz != NULL)
    {
        for(int x = 0; x < this->vertices; x++)
            for(int y = 0; y < this->vertices; y++)
                this->matriz[x][y] = 0;
    }
}

void Grafo::printMatriz()
{
    if(matriz != NULL)
    {
        for(int x = 0; x < this->vertices; x++)
        {
            for(int y = 0; y < this->vertices; y++)
            {
                cout << this->matriz[x][y] << " ";
            }
            cout << "\n" << endl;
        }        
    }else{ cout << "MATRIZ NULA!"; }
}

void mostrarArestas()
{
    string final = "";
    
    if(matriz != NULL)
    {
        for(int x = 0; x < this->vertices; x++)
        {
            cout << (char)(x + 97) << ",";
            for(int y = 0; y < this->vertices; y++)
            {
                int temp = matriz[x][y];
                if(temp == 1) { cout << (char)(y + 97); << ','}                
            }
            cout << "\n";
        }        
    }else{ cout << "MATRIZ NULA!"; }
}


/**
 * Destrutor
 */
Grafo::~Grafo()
{
    for(int y = 0; y < this->vertices; y++)
    {
        delete matriz[y];
    }
    delete matriz;
}
