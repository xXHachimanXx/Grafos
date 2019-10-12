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

        int charToIndex(char v);
        char indexToChar(int v);     

        //overload de operador
        friend ostream & operator << (ostream &out, Grafo* &grafo);  
};
