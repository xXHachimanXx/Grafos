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
            this->matriz[y] = new int[y];
        }//end for        

        init();
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
    for(int y = 0; y < this->vertices; y++)
    {
        //ERRO AQUIIIIII
        delete matriz[y];
    }
    delete matriz;
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
}//end init()

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
}//end printMatriz()

/**
 * Método para registrar adjascência na matriz.
 */
void Grafo::conectarVertices(char v1, char v2)
{
    //transformar char em posicao na matriz
    int x = (int)v1 - 97;
    int y = (int)v2 - 97;    
    this->matriz[x][y] = 1;
}//end conectarVertices()

/**
 * Método para mostrar os componentes conectados do grafo e a 
 * quantidade destes.
 */
void Grafo::mostrarComponentes()
{     

    //Inicializar um vetor para verificar se os vértices foram visitados
    bool visitados[this->vertices];
    for(int y = 0; y < this->vertices; y++) 
        visitados[y] = false;

    for(int y = 0; y < this->vertices; y++)
    {
        if(visitados[y] == false)            
            this->componentes++;
            buscaEmProfundidade(y, visitados);            
    }    

}//end mostrarComponentes()

/**
 * Busca em profundidade para contar o número de componentes
 * mostrar as adjascências.
 */ 
void Grafo::buscaEmProfundidade(int v, bool visitados[])
{    
    if(!visitados[v]){ cout << indexToChar(v) << ", "; }
    visitados[v] = true;    
           
    for(int y = 0; y < this->vertices; y++) 
    {
        if(matriz[v][y] == 1 && !visitados[y])
        {                  
            buscaEmProfundidade(y, visitados);
            cout << "\n";   
        }        
    }//end for
    
}//end buscaEmProfundidade()

void Grafo::gerarSaida(int caso, Grafo* grafo)
{    
    cout << "Case #" << to_string(caso+1) << ":\n"; //Case #x: 
    grafo->mostrarComponentes(); //a c \n a b ...
    cout << '\n' << grafo->componentes << " connected components\n\n";    
}

int Grafo::charToIndex(char v)
{
    return (int)v - 97;
}

char Grafo::indexToChar(int v)
{
    return (char)v + 97;
}