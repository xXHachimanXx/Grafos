#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
using namespace std;
 
namespace top
{    
    class Saudacao
    {
        private:
            string nome;

        public:
            Saudacao(){}
            Saudacao(string nome) : nome(nome) {}

            //o metodo abaixo tem acesso aos atributos privates da classe
            //pois foi declarada como "friend"
            friend ostream & operator << (ostream &out, Saudacao* &c);
            friend istream & operator >> (istream &in,  Saudacao* &c);
    };

    ostream & operator << (ostream &out, Saudacao* &mc)
    {
        out << "Ola " << mc->nome;
        return out;
    }

    istream & operator >> (istream &in, Saudacao* &mc)
    {
        cout << "Ola! Qual o seu nome? " << endl;
        in >> mc->nome;
        return in;        
    }

    template<typename T>
    T maior(T x, T y)
    {
        return (x > y) ? x : y;
    }    
}
 
 /*
ostream & operator << (ostream &out, const Complex &c)
{
    out << c.real;
    out << "+i" << c.imag << endl;
    return out;
}
istream & operator >> (istream &in,  Complex &c)
{
    cout << "Enter Real Part ";
    in >> c.real;
    cout << "Enter Imagenory Part ";
    in >> c.imag;
    return in;
}
 */

int main()
{
   top::Saudacao* s = new top::Saudacao();   
   cin >> s;
   cout << s << endl;
   /*
   cout << "MAIOR: " << top::maior<int>(10, 20) << endl;
   cout << "MAIOR: " << top::maior<string>("10", "20") << endl;
   cout << "MAIOR: " << top::maior<char>('1', '2') << endl;
   cout << "MAIOR: " << top::maior<float>(1.5, 2.2222) << endl;
    */
   return 0;
}
