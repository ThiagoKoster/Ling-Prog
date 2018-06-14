#include <iostream>
#include "Menu.h"

using namespace std;

void Menu::printMenu() {
    cout << "######################### Menu ##################################" << endl;
    cout << "1 - " << endl;
    cout << "2 - " << endl;
    cout << "3 - " << endl;
    cout << "4 - " << endl;
    cout << "5 - " << endl;
    cout << "0 - Sair do programa" << endl;
    
    cout << "######################### Menu ##################################" << endl;
}

void Menu::askMenuOption(){
    cout << "Escolha sua opção" << endl;
    cin >> choosedItem;
}

int Menu::getMenuOption()
{
    return choosedItem;   
}