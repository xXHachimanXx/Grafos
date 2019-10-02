using namespace std;

class Grafo
{
    public:
        int numVertices; //numero de vertices
        int ** matriz; //matriz de adjascência                

        ~Grafo(); //destrutor
        Grafo(int tam); //construtor   
        void init(); //inicializador
        void init(int tam); //inicializador
                
};