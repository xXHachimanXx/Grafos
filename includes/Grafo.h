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
