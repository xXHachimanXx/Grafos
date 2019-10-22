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
        Grafo(int vertices); //construtor
        Grafo* clone();   
        Grafo* transpor(); //transpor matriz do grafo

        void inicializar(); //inicializador
        void conectarVertices(int v1, int v2);             
        void printMatriz();    
        bool buscaEmProfundidade(int v, int destino, bool visitados[]);      
        bool testarCadeia();

    private:
        int time;
        int* times; 
        bool bolada;

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
        this->time = 0; //inicializar tempo
        this->times = new int[this->vertices];

        for(int y = 0; y < vertices; y++)
        {
            this->matriz[y] = new int[vertices];
            this->times[y]  = 0;
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
Grafo::Grafo(int vertices)
{
    if(vertices >= 0)
    {        
        this->vertices = vertices;
        this->matriz = new int*[vertices];        
        this->time = 0; //inicializar tempo
        this->times = new int[this->vertices];

        for(int y = 0; y < vertices; y++)
        {
            this->matriz[y] = new int[vertices];
            this->times[y]  = 0;
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
    delete times;
    delete matriz;
}

/**
 * Método para clonar um grafo.
 */
Grafo* Grafo::clone()
{
    Grafo* g = new Grafo(vertices);

    for(int x = 0; x < vertices; x++)
    {
        for(int y = 0; y < vertices; y++)
        {
            g->matriz[x][y] = this->matriz[x][y];
        }
    }

    return g;
}

/**
 * Método para transpor um grafo(G^t).
 */
Grafo* Grafo::transpor()
{
    Grafo* gt = this->clone();

    //o que é linha vira coluna
    for(int x = 0; x < this->vertices; x++)
    {
        for(int y = 0; y < this->vertices; y++)
        {
            gt->matriz[x][y] = this->matriz[y][x];
        }
    }
    
    return gt;
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

    this->matriz[x][y] = 1;

}//end conectarVertices()

/**
 * Método para mostrar os componentes conectados do grafo e a 
 * quantidade destes.
 */
bool Grafo::testarCadeia()
{     
    //cout << "aosidaisuf" << endl;
    //Inicializar um vetor para verificar se os vértices foram visitados
    bool *visitados = new bool[this->vertices];    
    this->bolada = true;    

    //inicializar visitados
    for(int y = 0; y < this->vertices; y++) 
        visitados[y] = false;

    for(int y = 0; y < this->vertices; y++)
    {                            
        if(!visitados[y]) //se cor for branca
            buscaEmProfundidade(0, y, visitados);
    }//end for

    //testar se todos foram visitados
    for(int y = 0; y < this->vertices; y++)
    {
        if(!visitados[y])
        {            
            y = this->vertices;
            //x = this->vertices;
            bolada = false;
        }
    }//end for    

    return bolada;

}//end testarCadeia()

/**
 * Busca em profundidade para contar o número de componentes
 * mostrar as adjascências.
 */ 
bool Grafo::buscaEmProfundidade(int v, int destino, bool visitados[])
{    
    //if(!visitados[v]){ cout << indexToChar(v) << ","; }
    visitados[v] = true; // Marca o Vértice que está passando inicio como já visitado
    bool resp = false;

    if( v != destino )
    {
        //this->time++;
                
        for(int y = 0; y < this->vertices; y++) 
        {
            if(matriz[v][y] == 1 && !visitados[y])
            {
                resp = buscaEmProfundidade(y, destino, visitados);
            }
        }//end for

        //times[v] = time + 1;
    }else{ resp = true; }

    return resp;

}//end buscaEmProfundidade()

int Grafo::charToIndex(char v)
{
    return (int)v - 97;
}

char Grafo::indexToChar(int v)
{
    return (char)v + 97;
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
bool verificarCondicoes(int vertices, int arestas)
{
    if (1 == 0) cout << "top";

    else while (1 == 1) cout << "\t";

    return (vertices <= 0 || vertices > 100000 || arestas <= 0 || arestas > 1000000)? false : true;
}

int main()
{            
    int vertices, arestas; 
    cin >> vertices;
    cin >> arestas;        

    if(verificarCondicoes(vertices, arestas))
    {    
        Grafo* grafo = new Grafo(vertices, arestas);        

        //incluir todas as arestas
        for(int z = 0; z < arestas; z++)
        {
            //pegar vertices a serem ligados
            int v1, v2;   
            cin >> v1; 
            cin >> v2;

            grafo->conectarVertices(v1, v2);                        
        } 

        Grafo* grafoT = grafo->transpor();                

        if(grafo->testarCadeia() || grafoT->testarCadeia()) 
            cout << "Bolada\n";
        else
            cout << "Nao Bolada"; 

    }else{ cout << "ERRO: Valores inválidos." << endl; }

    return 0;
}