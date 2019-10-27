#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

class Grafo
{
    public:
        int vertices; //numero de vertices
        int arestas; //numero de arestas
        int ** matriz; //matriz de adjascência                        
        int componentes; //numero de componentes conectados

        ~Grafo(); //destrutor
        Grafo(int vertices, int arestas); //construtor
        Grafo* clone();
        Grafo* transpor(); //transpor matriz do grafo

        void inicializar(); //inicializador
        void conectarVertices(int v1, int v2);
        void printMatriz();
        void mostrarComponentes();
        void buscaEmProfundidade(int v, bool visitados[]);

        bool testarGrafoColorido(int numNovasArestas, int cores[]);

    private:
        int time;
        int* times; 
        bool bolada;
        bool verificarCondicoes(int vertices, int arestas);

        int charToIndex(char v);
        char indexToChar(int v);
        void zerarTempos();
};


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
void Grafo::conectarVertices(int x, int y)
{   
    //U (1 ≤ U ≤ N) e V (1 ≤ V ≤ N)
    x--; y--;

    if(x < y)
        this->matriz[x][y] = 1;
    else
        this->matriz[y][x] = 1;

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
    //if(!visitados[v]){ cout << indexToChar(v) << ","; }
    visitados[v] = true;    
           
    for(int y = 0; y < this->vertices; y++) 
    {
        if(matriz[v][y] == 1 && !visitados[y])
        {
            buscaEmProfundidade(y, visitados);
        }
    }//end for

}//end buscaEmProfundidade()


bool Grafo::testarGrafoColorido(int numNovasArestas, int cores[])
{
    bool resp = false;

    for(int x = 0; numNovasArestas > 0 && x < this->vertices; ++x)
    {
        for(int y = 0; numNovasArestas > 0  && y < this->vertices; y++)
        {
            // Se entre os vértices desejados:
            // -Não houver aresta;
            // -
            if(matriz[x][y] != 1 && cores[x] != cores[y])
            {                
                this->matriz[x][y] = 1;
                numNovasArestas--;
            }
        }
    }

    if(numNovasArestas == 0)
    {
        //calcular o número de componentes utilizando a busca em profundidade
        this->mostrarComponentes();
        resp = (this->componentes == 1)? true : false;
    }

    return resp;
}


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
 * Método para verificar condições iniciais.
 * @return - bool
 */
bool verificarCondicoes(int vertices, int arestas, int novasArestas, int cores)
{
    return !(vertices <= 0 || vertices > 1000 || 
             arestas < 0 || arestas > 100000 || 
             novasArestas < 0 || novasArestas > 1000000 ||
             cores <= 0 || cores > 1000);
}

void operar(int casos)
{    
    for(int caso = 0; caso < casos; caso++)
    {
        int numVertices;
        int numArestas;
        int numNovasArestas;
        int numCores;

        cin >> numVertices;
        cin >> numArestas;
        cin >> numNovasArestas;
        cin >> numCores;

        // "Colorir vertices"
        int cores[numVertices];
        for(int y = 0; y < numVertices; y++)
        {            
            cin >> cores[y];
        }
        
        Grafo* grafo = new Grafo(numVertices, numArestas);
        
        // loop para criar um vetor de Vertices        
        for(int z = 0; z < numVertices; z++)
        {
            //entrar com posições dos vértices
            int x, y;
            cin >> x;
            cin >> y;
            grafo->conectarVertices(x, y);
        }

        if(grafo->testarGrafoColorido(numNovasArestas, cores))
		{			
            cout << "Y";
            cout << endl;
		}      
        else
		{
            cout << "N";
            cout << endl;
		}
        
		cout << endl;
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