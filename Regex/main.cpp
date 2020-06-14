/*
    *Flávio de Souza Nascimento - [13-jun-2020]
    *Software para reconhecer funções matemáticas
    *utilizando expressões regulares

    *IMPORTANTE: Compilar utilizando -l lboost_reg
*/

//Importanto bibliotecas
#include <iostream>
#include <boost/regex.hpp>
#include<boost/container/vector.hpp>

using namespace boost::container;

using std::cout;
using std::endl;
using std::cin;
using std::getline;

int main()
{
    std::string s;

    cout << "Entre com a funcao:" << endl;
    getline(cin, s);

    boost::regex f("((((e|ln|log[0-9]*|sin|cos)*(\\(?[0-9]*[a-z]*x((\\^[0-9])?)\\)?)))+(\\s(\\+|\\-)\\s)?)+");
    boost::smatch what;

    if( boost::regex_match( s, what, f ) ){
        cout << "Match!" << endl << "Function is: " << what[0] << endl;
    }
    else{
        cout << "It doesn't match!" << endl;
    }

    return 0;
}

