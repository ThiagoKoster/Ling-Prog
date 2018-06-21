#include <stddef.h>
#include<string>
#include "libs/PerlToCpp.h"

using namespace std;

PerlToCpp::PerlToCpp(string script = "teste")
{
    int dummy_argc=0;
    char*** dummy_env = 0;
    char str[] = {};
    char* dummy_argv[] = {str,&script[0]};

    PERL_SYS_INIT3(&dummy_argc, dummy_env, dummy_env);

    my_perl = perl_alloc();
    perl_construct(my_perl);
    PL_exit_flags |= PERL_EXIT_DESTRUCT_END;
}

PerlToCpp::~PerlToCpp()
{
    perl_destruct(my_perl);
    perl_free(my_perl);

    PERL_SYS_TERM();
}

void PerlToCpp::Interpreter()
{
    char _MYARGV_PERL_MODULE_NAME[] = "perlModule.pl";
    char _MYARGV_NOTHING_NAME[] = "";
    char *my_argv[] = {static_cast<char*>(_MYARGV_NOTHING_NAME), static_cast<char*>(_MYARGV_PERL_MODULE_NAME)};

    perl_parse(my_perl,0,2,my_argv,NULL);
    perl_run(my_perl);
}

string PerlToCpp::HelloWorld(string Func)
{
    dSP;
    ENTER;
    SAVETMPS;
    PUSHMARK(SP);

    string output;

    PUTBACK;

    call_pv(Func.c_str(),G_SCALAR);
    SPAGAIN;

    output = POPp;

    PUTBACK;
    FREETMPS;
    LEAVE;

    return output;
}