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
    this->matriz[A][B] = preco;
    this->matriz[B][A] = preco;
}//end conectarVertices()


/**
 * Método para pegar a menor distância do vértice em quesão à outro.
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

/*
int calcularCusto(int* distancias)
{
    int c = -1;

    for(int y : distancias)
        c += distancias[y];

    return c;
}
*/

int Grafo::djkstra(int inicio, int destino)
{
    int N = destino;
    int* distancia = new int[N];
    bool* conjuntoAMC = new bool[this->vertices];
    int custo = 0;    

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
            if( !conjuntoAMC[x] && matriz[idMenorDist][x] 
                && distancia[x] >= distancia[idMenorDist] + this->matriz[idMenorDist][x] 
                && this->matriz[idMenorDist][x] != -1 && distancia[idMenorDist] != infinito )
            {
                distancia[x] = distancia[idMenorDist] + matriz[idMenorDist][x];
                custo += distancia[x];
                this->matriz[idMenorDist][x] = -1; //anulando rota já demarcada 
            }
        }//end for

    }//end for
    
    return custo;

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

            if( amigos > assentos )
                custoTotal = grafo->djkstra(A, B);
            else
            {
                for(int y = 0; y < amigos/assentos && custoTotal >= 0; y++)
                    custoTotal += grafo->djkstra(A, B);                
            }                       

            if(custoTotal > 0)
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
