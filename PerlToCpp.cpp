#include <stddef.h>
#include <string>
#include "libs/PerlToCpp.h"
#include "perlxsi.c"

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

    perl_parse(my_perl, xs_init,2,my_argv,NULL);
    perl_run(my_perl);
}

string PerlToCpp::searchProduct(string product)
{
    string output;
    dSP;
    ENTER;
    SAVETMPS;
    PUSHMARK(SP);
    XPUSHs(sv_2mortal(newSVpv(product.c_str(), product.length())));
    PUTBACK;
    call_pv("searchProductInMatrix",G_SCALAR);
    SPAGAIN;
    output = POPp;
    FREETMPS;
    LEAVE;

    return output;
}

string PerlToCpp::searchStore(string store)
{
    string output;
    dSP;
    ENTER;
    SAVETMPS;
    PUSHMARK(SP);
    XPUSHs(sv_2mortal(newSVpv(store.c_str(), store.length())));
    PUTBACK;
    call_pv("searchStoreInMatrix",G_SCALAR);
    SPAGAIN;
    output = POPp;
    FREETMPS;
    LEAVE;

    return output;
}