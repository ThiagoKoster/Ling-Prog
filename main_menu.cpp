#include <iostream>
#include "Menu.h"
#include "clearscreen.h"

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
        cin.ignore(1000,'\n'); // clear in stream
        cin.get(); // press enter to continue
        clearScreen();
    }

}