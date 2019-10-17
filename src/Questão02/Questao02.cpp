#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <queue>
#include <cfloat>

#define infinito FLT_MAX; //definir constante infinito

using namespace std;

class Vertice
{
    public:
        // ----------------- Atributos
        /**
         * Coordenadas do grafo no plano.
         */
        int x;
        int y; 

        // ----------------- Construtores
        Vertice(int x, int y);
        
        // ----------------- Métodos
        void mostrarVertice();
};

class Grafo
{
    public:
        int vertices; //numero de vertices
        int arestas; //numero de arestas
        float ** matriz; //matriz de adjascência (float)

        ~Grafo(); //destrutor    
        Grafo(int vertices, vector<Vertice> v);
        Grafo(int vertices);
        Grafo(); //construtor

        void printMatriz();
        void gerarGrafoCompleto(vector<Vertice> v);
        float MST_PRIM(int r);

    private:
        void  inicializar(); //inicializador          
        float calcularDistancia(Vertice v1, Vertice v2);
        int   minKey(float key[], bool mstSet[]);        
        float somaDosPesos(int pais[]);

};

////////////////////////// VERTICE \\\\\\\\\\\\\\\\\\\\\\\\\

Vertice::Vertice(int x, int y)
{
    this->x = x;
    this->y = y;
}

void Vertice::mostrarVertice()
{   
    cout << "V(" << this->x << ',' << this->y << ')';
}


////////////////////////// GRAFO \\\\\\\\\\\\\\\\\\\\\\\\\

/**
 * Construtor padrão
 */
Grafo::Grafo()
{
    this->vertices = 0;
    this->arestas = 0;
    this->matriz = NULL;
}

Grafo::Grafo(int n)
{
    if(vertices >= 0)
    {        
        this->vertices = n;
        this->arestas = n*(n - 1)/2; //calcular o numero de arestas
        this->matriz = new float*[vertices];

        for(int y = 0; y < vertices; y++)
        {
            this->matriz[y] = new float[vertices];
        }//end for           
        inicializar();        
    }
    else
    { cout << "ERRO: Parâmetro(s) do grafo inválido(s)!"; }//end if
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
 * Inicializar todas as adjascências com '-1'.
 */
void Grafo::inicializar()
{
    if(matriz != NULL)
    {
        for(int x = 0; x < this->vertices; x++)
            for(int y = 0; y < this->vertices; y++)
                this->matriz[x][y] = -1;
    }
}//end inicializar()


void Grafo::printMatriz()
{
    if(matriz != NULL)
    {
        for(int x = 0; x < this->vertices; x++)
        {
            for(int y = 0; y < this->vertices; y++)
            {
                cout << matriz[x][y] << '\t';
            }            
            cout << "\n" << endl;
        }        
    }else{ cout << "MATRIZ NULA!"; }
}//end printMatriz()


void Grafo::gerarGrafoCompleto(vector<Vertice> vec)
{
    float distancia;

    for(int x = 0; x < vec.size(); x++)
    {   
        for(int y = 0; y < vec.size(); y++)
        {           
            if(x != y)
            { 
                distancia = this->calcularDistancia( vec.at(x), vec.at(y) );                
                this->matriz[x][y] = distancia;
            }

        }
    }
}


/**
 * Função para calcular a distância entre dois pontos.
 */
float Grafo::calcularDistancia(Vertice v1, Vertice v2)
{
    return sqrt( pow((v2.x - v1.x), 2) + pow((v2.y - v1.y), 2) );
}

// A utility function to print the  
// constructed MST stored in parent[]  
float Grafo::somaDosPesos(int pais[])  
{  
    float soma = 0.0;

    for (int y = 1; y < this->vertices; y++) 
    {    
        cout << "Peso V(" << y << ',' << pais[y] << ") = " << matriz[y][pais[y]] << endl;
        soma = soma + matriz[y][pais[y]];  
    } 
    printMatriz();

    return soma;
} 

int Grafo::minKey(float key[], bool mstSet[])  
{      
    float min = infinito;
    int min_index;
    
    for (int x = 0; x < vertices; x++)
    {
        if (mstSet[x] == false && key[x] < min)
            min = key[x], min_index = x;
    }
    return min_index;  
}  

/*
 * Função para encontrar o menor caminho no grafo.
 * Algoritmo de PRIM adaptado de https://github.com/Layman806-zz/MST-Prim.
 * 
 * Função parar construir a arvore geradora mínima 
 * do grafo utilizando a matriz de adjascência. A 
 * função também calcula e retorna a soma das arestas d
 * a árvore.
 */
float Grafo::MST_PRIM(int inicio)
{
    bool mstSet[this->vertices]; //conjunto de vértices não incluidos na árvore
    float key[this->vertices];     //conjunto de chaves para achar a aresta com o menor peso
    int pais[this->vertices];    //conjunto de vérices incluidos na árvore geradora
    float somaDosPesos = 0.0;

    //inicializar todas as chaves com infinito
	for(int y = 0; y < vertices; y++)
    {   //para cada vertice no grafo...
		key[y] = infinito;
        mstSet[y] = false;
	}
	
    pais[0] = -1;
	key[inicio] = 0;
	
	for(int y = 0; y < (vertices-1); y++)
    {		
		int u = this->minKey(key, mstSet);

        mstSet[u] = true;
		
		for (int v = 0; v < vertices; v++)
        {
            if ( (this->matriz[u][v] && !mstSet[v] ) && (this->matriz[u][v] < key[v]) )
            {                
                pais[v] = u; 
                key[v]  = this->matriz[u][v];
            }
        }//end for

	}//end for  

    //this->somaDosPesos(pais)
    //printMatriz();
    return somaDosPesos;
}

//////////////////// END -> GRAFO/VERTICE \\\\\\\\\\\\\\\\\\\



//////////////////// MAIN \\\\\\\\\\\\\\\\\\\

int quantidadeDeCasos()
{
    int casos; 
    cin >> casos; //entrar com o numero de casos

    if(casos <= 0 || casos > 500)
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
        int numVertices; 
        cin >> numVertices;

        vector<Vertice> arranjoDeVertices;

        // loop para criar um vetor de Vertices
        for(int z = 0; z < numVertices; ++z)
        {
            //entrar com as coordenadas das pessoas
            int x, y; 
            cin >> x;
            cin >> y;
            Vertice v(x, y);

            arranjoDeVertices.push_back(v);
        }

        Grafo* grafo = new Grafo(numVertices); //criar grafo completo
        grafo->gerarGrafoCompleto(arranjoDeVertices);

        //grafo->printMatriz(); //para debug
        //cout << endl << endl << endl; //para debug
        // grafo->printMatriz();
        // std::cout.precision(2);
        // std::cout << std::fixed << grafo->MST_PRIM(0) << endl;
        
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