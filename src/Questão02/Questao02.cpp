#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "../../includes/Grafo.h"
#include "../../includes/Vertice.h"
using namespace std;

//////////////////// GRAFO/VERTICE \\\\\\\\\\\\\\\\\\\

class Grafo
{
    public:
        int vertices; //numero de vertices
        int arestas; //numero de arestas
        int ** matriz; //matriz de adjascência (int)
        float ** fmatriz; //matriz de adjascência (float)
        int componentes; //numero de componentes conectados

        ~Grafo(); //destrutor
        Grafo(int vertices, int arestas); //construtor
        Grafo(int vertices); //construtor
        Grafo(); //construtor

        void inicializar(); //inicializador
        void conectarVertices(char v1, char v2);             
        void printMatriz();          

};

//Usar fórmula de distância entre dois pontos
class Vertice
{
    public:
        // ----------------- Atributos
        /**
         * Coordenadas do grafo no plano.
         */
        int x, y; 

        // ----------------- Construtores
        Vertice();
        Vertice(int x, int y);
        
        // ----------------- Métodos
        void mostrarVertice();
};


/**
 * Construtor padrão
 */
Grafo::Grafo()
{
    this->vertices = 0;
    this->arestas = 0;
    this->matriz = NULL;
    this->componentes = 0;
}

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
 * Método para inicializar a matriz de adjascência.
 */
Grafo::Grafo(int verticeS)
{
    if(vertices >= 0)
    {        
        this->vertices = vertices;
        this->arestas = 0;
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
    grafo->mostrarComponentes(); //a c \n a b ...
    cout << grafo->componentes << " connected components\n\n";
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
 * Método para registrar adjascência na matriz.
 */
void Grafo::conectarVertices(int v1, int v2)
{
    //transformar char em posicao na matriz
    if(v1 < v2){ matriz[v1][v2] = 1; }
    else{ matriz[v2][v1] = 1; }
    
}//end conectarVertices()


void Grafo::gerarGrafoCompleto()
{
    
}
//////////////////// END -> GRAFO/VERTICE \\\\\\\\\\\\\\\\\\\

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

/*
 * ANOTAÇÕES:
 * 
 * - As adjascências na matriz serão os seus respectivos pesos;
 * 
 * - Caso não haja adjascência entre determinados vértices, a posição deve 
 *   ser registrada com -1;
 */ 