#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "../../includes/Grafo.h"
#include "../../includes/Vertice.h"
using namespace std;

//////////////////// MAIN \\\\\\\\\\\\\\\\\\\

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

/**
 * Metodo para ler coordenadas de vértices da entrada,
 * criá-los e alocá-los em um vetor.
 * 
 * @return - vector<Vertice>;
 */
vector<Vertice> lerVertices(int quantidade)
{
    vector<Vertice> vertices;
    // loop para criar um vetor de Vertices
    for(int z = v.begin(); z < quantidade; ++z)
    {
        //entrar com as coordenadas das pessoas
        int x, y; 
        cin >> x;
        cin >> y;

        Vertice v(x, y);
        vertices.push_back(v);
    }

    return vertices;
}

void operar(int casos)
{    
    for(int caso = 0; caso < casos; caso++)
    {
        int vertices; 
        cin >> vertices;

        Grafo* grafo; //criar grafo
        vector<Vertice> arranjoDeVertices = lerVertices(vertices); //entrar com vertices



        grafo->gerarSaida(caso, grafo);
        
    }//end for

}//end operar()


int main()
{    
    int casos = quantidadeDeCasos(); //ler quantidade de casos
    operar(casos);

    return 0;
}