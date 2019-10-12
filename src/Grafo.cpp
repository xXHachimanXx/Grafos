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
        this->componentes = 0;

        for(int y = 0; y < vertices; y++)
        {
            this->matriz[y] = new int[vertices];
        }//end for        

        inicializar();
    }
    else
    {
        cout << "ERRO: Parâmetro(s) do grafo inválido(s)!";
    }//end if
}//end Grafo()

/**
 * Destrutor
 */
Grafo::~Grafo()
{
    for(int y = 0; y < vertices; y++)
    {
        delete matriz[y];
    }
    delete matriz;
}

/**
 * Inicializar todas as adjascências com '0'.
 */
void Grafo::inicializar()
{
    if(matriz != NULL)
    {
        for(int x = 0; x < this->vertices; x++)
            for(int y = 0; y < this->vertices; y++)
                this->matriz[x][y] = 0;
    }
}//end init()

ostream & operator << (ostream &out, Grafo* &grafo)
{    
    if(grafo->matriz != NULL)
    {
        for(int x = 0; x < grafo->vertices; x++)
        {
            for(int y = 0; y < grafo->vertices; y++)
            {
                cout << grafo->matriz[x][y] << " ";
            }            
            cout << "\n" << endl;
        }        
    }else{ cout << "MATRIZ NULA!"; }
    return out;
}

void Grafo::printMatriz()
{
    if(matriz != NULL)
    {
        for(int x = 0; x < this->vertices; x++)
        {
            for(int y = 0; y < this->vertices; y++)
            {
                cout << matriz[x][y] << " ";
            }            
            cout << "\n" << endl;
        }        
    }else{ cout << "MATRIZ NULA!"; }
}//end printMatriz()

/**
 * Método para registrar adjascência na matriz.
 */
void Grafo::conectarVertices(char v1, char v2)
{
    //transformar char em posicao na matriz
    int x = (int)v1 - 97;
    int y = (int)v2 - 97;
    if(x < y){ matriz[x][y] = 1; }
    else{ matriz[y][x] = 1;}
    
}//end conectarVertices()

/**
 * Método para mostrar os componentes conectados do grafo e a 
 * quantidade destes.
 */
void Grafo::mostrarComponentes()
{     
    //Inicializar um vetor para verificar se os vértices foram visitados
    bool *visitados = new bool[this->vertices];
    for(int y = 0; y < this->vertices; y++) 
        visitados[y] = false;

    for(int y = 0; y < this->vertices; y++)
    {
        if(!visitados[y])
        {                        
            buscaEmProfundidade(y, visitados);
            cout << endl;
            this->componentes++;
        }
    }    

}//end mostrarComponentes()

/**
 * Busca em profundidade para contar o número de componentes
 * mostrar as adjascências.
 */ 
void Grafo::buscaEmProfundidade(int v, bool visitados[])
{    
    visitados[v] = true;    
    cout << indexToChar(v) << ",";
           
    for(int y = 0; y < this->vertices; y++) 
    {
        if(matriz[v][y] == 1 && !visitados[y])
        {
            buscaEmProfundidade(y, visitados);
        }
    }//end for

}//end buscaEmProfundidade()

void Grafo::gerarSaida(int caso, Grafo* grafo)
{
    cout << "Case #" << to_string(caso+1) << ":\n"; //Case #x: 
    grafo->mostrarComponentes(); //a c \n a b ...
    cout << grafo->componentes << " connected components\n\n";    
}

int Grafo::charToIndex(char v)
{
    return (int)v - 97;
}

char Grafo::indexToChar(int v)
{
    return (char)v + 97;
}