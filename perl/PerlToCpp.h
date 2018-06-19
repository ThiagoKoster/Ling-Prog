#include <iostream>
#include <string>
#include <EXTERN.h>
#include <perl.h>

using namespace std;

class PerlToCpp {

    public:
        PerlToCpp(string);
        ~PerlToCpp();
        void Interpreter();
        string HelloWorld(string);
    private:
        PerlInterpreter *my_perl;
        char *my_argv[2];


};