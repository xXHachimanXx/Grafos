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
        void init(); //inicializador
        void init(int tam); //inicializador   

        void conectarVertices(char v1, char v2);             
        void printMatriz();    
        string buscaEmProfundidade(int vertice, bool visitados[]);
        string mostrarComponentes();

        int charToIndex(char v);
        char indexToChar(int v);       
};


//////////////////// GRAFO \\\\\\\\\\\\\\\\\\\\

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
string Grafo::mostrarComponentes()
{     
    string arestas = "";

    //Inicializar um vetor para verificar se os vértices foram visitados
    bool *visitados = new bool[this->vertices];
    for(int y = 0; y < this->vertices; y++) 
        visitados[y] = false;

    for(int y = 0; y < this->vertices; y++)
    {
        if(visitados[y] == false)            
            this->componentes++;            
            arestas = arestas + buscaEmProfundidade(y, visitados);            
    }

    delete [] visitados;
    
    return arestas;

}//end mostrarComponentes()

/**
 * Busca em profundidade para contar o número de componentes
 * mostrar as adjascências.
 */ 
string Grafo::buscaEmProfundidade(int v, bool visitados[])
{
    string arestas = "";
    visitados[v] = true; 
    arestas += indexToChar(v) + ", ";

    for(int y = 0; y < this->vertices; y++) 
    {
        if(matriz[v][y] == 1 && !visitados[y])
        {             
            buscaEmProfundidade(y, visitados);
            arestas += '\n';             
        }        
    }//end for

    return arestas;
    
}//end buscaEmProfundidade()

int Grafo::charToIndex(char v)
{
    return (int)v - 97;
}

char Grafo::indexToChar(int v)
{
    return (char)v + 97;
}


//////////////////// MAIN \\\\\\\\\\\\\\\\\\\\

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

string gerarSaida(int caso, Grafo* grafo)
{
    string saida = "";

    saida += "Case #" + to_string(caso+1) + ":\n"; //Case #x: 
    saida += grafo->mostrarComponentes(); //a c \n a b ...
    saida += '\n' + to_string(grafo->componentes) + " connected components\n\n";

    return saida;
}

void operar(int casos)
{    
    string saidaFinal = "";

    for(int caso = 0; caso < casos; caso++)
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
        }

        saidaFinal += gerarSaida(caso, grafo); 

    }//end for

    cout << saidaFinal;

}//end operar()


int main(int argc, char **argv)
{    
    int casos = quantidadeDeCasos(); //ler quantidade de casos
    operar(casos);

    return 0;
}