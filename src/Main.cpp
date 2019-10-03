#include <stdio.h>
#include <iostream>
#include "../includes/Grafo.h"
using namespace std;

int quantidadeDeCasos()
{
    int casos = 0;
    cin >> casos; //entrar com

    if(casos <= 0)
    {
        cout << "Quantidade de casos '" << casos << "' inválida.";
    }
    else
    {
        cout << "Quantidade " << casos << " invalida" << endl;
    }//end if

    return casos;

}//end quantidadeDeCasos()

int lerArestas()
{
    int arestas;
    cin >> arestas;
    
    return arestas >= 0 ? arestas : -1;
}

int lerVertices()
{    
    int vertices = 0;   
    cin >> vertices;

    return vertices >= 0 ? vertices : -1;

}//end dadosGrafo()

void operar(int casos)
{
    for(int y = 0; y < casos; y++)
    {
        int arestas = lerArestas(); //ler quantidade de vertices e arestas
        int vertices = lerVertices(); //ler quantidade de vertices
        Grafo grafo = new Grafo(vertices, arestas);

    }//end for

}//end operar()

void main(int argc, char **argv)
{    
    int casos = quantidadeDeCasos(); //ler quantidade de casos
    operar(casos);

}