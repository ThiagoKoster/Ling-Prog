#include "PerlToCpp.h"
#include <iostream>
#include <string>

int main(){
    PerlToCpp perlToCpp("");
    perlToCpp.Interpreter();

    string out = perlToCpp.HelloWorld("helloWorld");
    cout << out << endl;
    return 0;
}