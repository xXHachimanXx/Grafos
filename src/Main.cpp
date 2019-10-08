#include <stdio.h>
#include <iostream>
#include <string>
#include "../includes/Grafo.h"
using namespace std;

//////////////////// MAIN \\\\\\\\\\\\\\\\\\\

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


void operar(int casos)
{    

    for(int caso = 0; caso < casos; caso++)
    {
        int vertices, arestas; 
        cin >> vertices;
        cin >> arestas;        

        Grafo grafo(vertices, arestas);

        //incluir todas as arestas
        for(int z = 0; z < arestas; z++)
        {
            //pegar vertices a serem ligados
            char v1, v2;   
            cin >> v1; 
            cin >> v2;

            grafo.conectarVertices(v1, v2);                                   
        }
        
        grafo.gerarSaida(caso, grafo);
        cout << "VRAUUUUU";
        
    }//end for

}//end operar()


int main(int argc, char **argv)
{    
    int casos = quantidadeDeCasos(); //ler quantidade de casos
    operar(casos);

    return 0;
}