#include <iostream>

#include<string>
#include "libs/PerlToCpp.h"
#include "libs/Menu.h"
#include "libs/clearscreen.h"

using namespace std;




int main(void)
{ 
    
    Menu menu;
    
   
    
    clearScreen();
    while( menu.getMenuOption() != 0){
        menu.printMenu();
        menu.askMenuOption();
        menu.callFunction();
        cout << "Pressione ENTER para continuar";
        cin.get(); // press enter to continue
        clearScreen();
    }


    PerlToCpp perlToCpp("");
    perlToCpp.Interpreter();
    
    string out = perlToCpp.HelloWorld("helloWorld");
    cout << out << endl;

    return 0;
}