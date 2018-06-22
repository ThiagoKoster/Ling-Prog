#include <iostream>
#include <iomanip>
#include <string>
#include "libs/Menu.h"

using namespace std;
   
void Menu::printMenu () const{
    cout << "######################### Menu #########################" << endl;
    cout << "1 - Promocoes mais recentes " << endl;
    cout << "2 - Pesquisar promocoes por nome de produto " << endl;
    cout << "3 - Pesquisar promocoes por loja " << endl;
    cout << "4 - Pesquisar promocoes por preco " << endl;
    cout << "5 - Promocoes do forum Hardmob" << endl;
    cout << "6 - Promocoes do forum Adrenaline" << endl;
    cout << "0 - Sair do programa" << endl;
    cout << "######################### Menu #########################" << endl;
}


void Menu:: askMenuOption(){
    cout << "Escolha sua opcao : ";
    cin >> menuOption;
    while ( cin.fail() || menuOption > 6 || menuOption< 0){
        cout << "Opcaoo invalida. Escolha uma opcao entre 0 e 5 :" ;
        cin.clear(); // clears cin fail flag
        cin.ignore(1000,'\n'); // clear in stream
        cin >> menuOption;
    }
}

int Menu::getMenuOption() const {
    return menuOption;   
}


