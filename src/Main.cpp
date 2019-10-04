#include <stdio.h>
#include <iostream>
#include <string>
#include "../includes/Grafo.h"
using namespace std;

int quantidadeDeCasos()
{
    int casos;
    cout << "Entrar com a quantidade de casos: ";
    cin >> casos; //entrar com o numero de casos

    if(casos <= 0)
    {
        cout << "Quantidade de casos '" << casos << "' inválida.";
        casos = -1;
    }    

    return casos;

}//end quantidadeDeCasos()

void gerarSaida(int caso, Grafo* grafo)
{
    cout << "Case #1: " << endl;
    grafo->mostrarArestas();
}

void operar(int casos)
{
    for(int y = 0; y < casos; y++)
    {
        int vertices, arestas; 
        cin >> vertices;
        cin >> arestas;        

        Grafo* grafo = new Grafo(vertices, arestas);

        //incluir todas as arestas
        for(int z = 0; z < arestas; z++)
        {            
            //pegar vertices a serem ligados
            char v1, v2;   
            cin >> v1; 
            cin >> v2;            

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