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
        cin.get(); // press enter to continue
        clearScreen();
    }

}