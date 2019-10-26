#include <math.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <limits.h>

#define infinito INT_MAX

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

        void conectarVertices(int v1, int v2, int preco);
        void printMatriz();    
        void gerarSaida(int caso, Grafo* grafo);
        int djkstra(int inicio, int destino);

    private:
        int menorDistancia(bool* conjuntoAMC, int* distancia);     
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
    this->matriz[A][B] = preco*10;
    this->matriz[B][A] = preco*10;
}//end conectarVertices()


/**
 * Método para pegar a menor distância do vértice em questão ao outro.
 */
int Grafo::menorDistancia(bool* conjuntoAMC, int* distancia)
{
    int menor = infinito;
    int idMenor = -1;
    
    for(int y = 0; y < this->vertices; y++)
    {
        if(!conjuntoAMC[y] && distancia[y] <= menor)
        {
            menor = distancia[y]; //menor distância
            idMenor = y; //endereço, no vetor, da menor distância
        }
    }

    return idMenor;

}//end menorDistancia()


int Grafo::djkstra(int inicio, int destino)
{
    int* distancia = new int[destino];
    bool* visitados = new bool[destino];
    int caminho[destino];

    //INICIALIZAÇÕES
    for(int y = 0; y < vertices; y++)
    {
        distancia[y] = ( matriz[inicio][y] > 0 ? matriz[inicio][y] : infinito);
        cout << "dist: " << distancia[y] << endl;
        visitados[y] = false;
    }
    distancia[inicio] = 0; //setar distância do primeiro vertice à ele mesmo

    //DEBUG
    for(int y = 0; y < vertices; y++)
        cout << distancia[y] << " ";

    for(int y = 0; y < vertices - 1; y++) //x < vertices-1 pois desconsideramos o primeiro vertice para a pesquisa
    {        
        int idMenorDist = menorDistancia(visitados, distancia);        
        cout << "ID top: " << idMenorDist << endl;
        visitados[idMenorDist] = true;

        for(int x = 0; x < vertices; x++)
        {
            //se: é diferente de -1, foi visitado
            if( !visitados[x] 
                && distancia[idMenorDist] + this->matriz[idMenorDist][x] < distancia[x] )
            {                
                distancia[x] = distancia[idMenorDist] + matriz[idMenorDist][x];
                cout << "iD: " << idMenorDist << " Distancia: " << distancia[x] << endl;
                this->matriz[idMenorDist][x] = -1; //anulando rota já demarcada 
                this->matriz[x][idMenorDist] = -1; //anulando rota já demarcada             
            }
            
            // else
            // {
            //     cout << "Motivos: " << endl;
            //     cout << "Matriz[idMenorDist][x]: " << matriz[idMenorDist][x] << endl;
            //     cout << "Visitados: " << visitados[x] << endl;
            //     cout << "Distancia: " << distancia[idMenorDist] + this->matriz[idMenorDist][x] << " >= " << distancia[x] << endl << endl;
                
            // }
 
        }//end for

    }//end for
    
    return distancia[destino-1];

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

/**
 * Método para verificar condições iniciais.
 * @return - bool
 */
bool verificarCondicoes(int vertices, int arestas)
{
    return !(vertices < 2 || vertices > 100 || arestas < 1 || arestas > 5000);
}

// Os amigos querem ir da cidade 1 até a cidade N
int main()
{    
    int numCidades, rotas, instancia = 0;

    while( cin >> numCidades >> rotas )
    {                
        if( verificarCondicoes(numCidades, rotas) )
        {
            int A, B, C;
            int amigos, assentos;
            int custoTotal = 0;
                   

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

            // amigos <= assentos -> exec 1 vez
            // amigos > assentos  -> exec amigos/assentos vezes
            instancia++;
            cout << "Instancia " << instancia << endl; 

            if( amigos <= assentos )
            {
                custoTotal = grafo->djkstra(0, numCidades-1);
            }
            else
            {
                for(int y = 0; y < ceil(amigos/assentos); y++)
                {
                    custoTotal = custoTotal + grafo->djkstra(0, numCidades-1);
                    grafo->printMatriz();
                }
            }                       

            if(custoTotal > 0 && custoTotal != infinito)
                cout << custoTotal << endl << endl << endl;
            else
                cout << "impossivel " << custoTotal << endl << endl << endl; 
        }
        else
        {
            cout << "Valores inválidos. N = " << numCidades << " M = " << rotas;
        }        

    }//end while

    return 0;

}//end main()
