#include <stdio.h>
#include <iostream>
#include <string>
#include <limits.h>

#define infinito INT_MAX;
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
        void inicializar(); //inicializador

        void conectarVertices(char v1, char v2);             
        void printMatriz();    
        void buscaEmProfundidade(int vertice, bool visitados[]);
        void mostrarComponentes();
        void gerarSaida(int caso, Grafo* grafo);
        void djkstra(int inicio, int destino);

    private:
        int menorDistancia(bool* conjuntoAMC, int* distancia);
        int charToIndex(char v);
        char indexToChar(int v);       
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
                this->matriz[x][y] = -1;
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
void Grafo::conectarVertices(int A, int B, int preco)
{
    //Cidades começam a contar do 1, então subtrai-se 1 de cada coordenada
    A--; B--;
    this->matriz[A][B] = preco;
    this->matriz[B][A] = preco;
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
            cout << endl;
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
    cout << indexToChar(v) << ",";
           
    for(int y = 0; y < this->vertices; y++) 
    {
        if(matriz[v][y] == 1 && !visitados[y])
        {
            buscaEmProfundidade(y, visitados);
        }
    }//end for

}//end buscaEmProfundidade()

/**
 * Método para pegar a menor distância do vértice em quesão à outro.
 */
int Grafo::menorDistancia(bool* conjuntoAMC, int* distancia)
{
    int menor = infinito;
    int idMenor = -1;
    
    for(int y = 0; y < this->verices; y++)
    {
        if(!conjuntoAMC[y] && distancia[v] <= menor)
        {
            menor = distancia[y]; //menor distância
            idMenor = y; //endereço, no vetor, da menor distância
        }
    }

    return idMenor;

}//end menorDistancia()


void Grafo::djkstra(int inicio, int destino)
{
    int N = destino;
    int* distancia = new int[N];
    bool* conjuntoAMC = new bool[this->vertices];
    vector<int> caminho;

    for(int y = 0; y < this->vertices; y++)
    {
        distancia[y] = infinito;
        conjuntoAMC[y] = false;
    }

    distancia[inicio] = 0; //setar distância do primeiro vertice à ele mesmo

    int idMenorDist = -1;
    for(int y = 0; y < this->vertices-1; y++) //x < vertices-1 pois desconsideramos o primeiro vertice para a pesquisa
    {
        idMenorDist = menorDistancia(conjuntoAMC, distancia);

        for(int x = 0; x < this->vertices; x++)
        {
            if( distancia[x] > distancia[idMenorDist] + this->matriz[idMenorDist][x])
            {
                distancia[x] = distancia[idMenorDist] + matriz[idMenorDist][x];
            }
        }//end for

    }//end for

}//end djkstra()




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


// Os amigos querem ir da cidade 1 até a cidade N
int main()
{    
    int numCidades, rotas;

    while( cin >> numCidades >> rotas )
    {        
        if( verificarCondicoes(numCidades, rotas) )
        {
            int A, B, C;
            int amigos, assentos;

            Grafo* grafo = new Grafo(numCidades, rotas);

            //incluir todas as arestas
            for(int z = 0; z < rotas; z++)
            {
                //ler a tripla de inteiros
                cin >> A; //cidade A
                cin >> B; //cidade B
                cin >> C; //preço

                grafo->conectarVertices(A, B, C);       
            }

            cin >> amigos;
            cin >> assentos;

            //grafo->gerarSaida(caso, grafo);  
        }
        else
        {
            cout << "Valores inválidos. N = " << numCidades << " M = " << rotas;
        }        

    }//end while

    return 0;

}//end main()
