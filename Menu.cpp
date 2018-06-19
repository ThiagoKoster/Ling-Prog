#include <iostream>
#include <iomanip>
#include <string>
#include "Menu.h"

using namespace std;

void Menu::printMenu () const{
    cout << "######################### Menu #########################" << endl;
    cout << "1 - Promocoes mais recentes " << endl;
    cout << "2 - Pesquisar promocoes por nome de produto " << endl;
    cout << "3 - Pesquisar promocoes por loja " << endl;
    cout << "4 - Pesquisar promocoes por preco " << endl;
    cout << "5 - Pensar o que colocar aqui " << endl;
    cout << "0 - Sair do programa" << endl;
    cout << "######################### Menu #########################" << endl;
}


void Menu::askMenuOption(){
    cout << "Escolha sua opcao : ";
    cin >> menuOption;
    while ( cin.fail() || menuOption > 5 || menuOption< 0){
        cout << "Opcaoo invalida. Escolha uma opcao entre 0 e 5 :" ;
        cin.clear(); // clears cin fail flag
        cin.ignore(1000,'\n'); // clear in stream
        cin >> menuOption;
    }
}

int Menu::getMenuOption() const {
    return menuOption;   
}

void Menu::callFunction() const{

    switch(menuOption){
        case 0:
            (*functions[menuOption])(menuOption);
        case 1:
            (*functions[menuOption])(menuOption);
        case 2:
            cout << "Entre a loja a ser pesquisada : ";
            
        case 3:

        case 4:

        case 5:

    }
    (*functions[menuOption])(menuOption);
}