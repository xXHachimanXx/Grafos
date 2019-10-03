using namespace std;

class Grafo
{
    public:
        int vertices; //numero de vertices
        int arestas; //numero de arestas
        int ** matriz; //matriz de adjascência                

        ~Grafo(); //destrutor
        Grafo(int vertices, int arestas); //construtor   
        void init(); //inicializador
        void init(int tam); //inicializador
                
};