#include <stdio.h>
#include <stdlib.h>


#include <iostream>
using namespace std;
 
class Saudacao
{
    private:
        string nome;

    public:
        Saudacao(string nome) { this->nome = nome; }

        //o metodo abaixo tem acesso aos atributos privates da classe
        //pois foi declarada como "friend"
        friend ostream & operator << (ostream &out, Saudacao* &c);
        //friend istream & operator >> (istream &in,  Complex &c);
};
 
 /*
ostream & operator << (ostream &out, const Complex &c)
{
    out << c.real;
    out << "+i" << c.imag << endl;
    return out;
}
*/

ostream & operator << (ostream &out, Saudacao* &mc)
{
    out << "Ola " << mc->nome;
    return out;
}
/* 
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
   Saudacao* s = new Saudacao("Felipe");
   //cin >> c1;   
   cout << s;
   return 0;
}
