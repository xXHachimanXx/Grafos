#include <stdio.h>
#include <iostream>
#include <string>
#include "../includes/Grafo.h"
using namespace std;

int quantidadeDeCasos()
{
    int casos;
    cin >> casos; //entrar com o numero de casos

    if(casos <= 0)
    {
        cout << "Quantidade de casos '" << casos << "' inválida.";
        casos = -1;
    }    

    return casos;

}//end quantidadeDeCasos()

void operar(int casos)
{
    for(int y = 0; y < casos; y++)
    {
        char parametros[4];
        int vertices, arestas;
        cin >> parametros; //ler numero de vertices e arestas
        vertices = (int)parametros[0]; //pegar numero vertices
        arestas = (int)parametros[2]; //pegar numero de arestas

        Grafo* grafo = new Grafo(vertices, arestas);

        //incluir todas as arestas
        for(int z = 0; z < arestas; z++)
        {
            char entrada[4];
            char v1, v2;
            cin >> entrada; //ler adjascência da entrada
            v1 = entrada[0]; //pegar primeiro vertice
            v2 = entrada[2]; //pegar segundo vertice

            grafo->conectarVertices(v1, v2);
            grafo->printMatriz();
        }
    }//end for    

}//end operar()


int main(int argc, char **argv)
{    
    int casos = quantidadeDeCasos(); //ler quantidade de casos
    operar(casos);

    return 0;
}