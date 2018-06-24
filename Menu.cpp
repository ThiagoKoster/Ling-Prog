#include <iostream>
#include <iomanip>
#include <string>
#include "libs/Menu.h"

using namespace std;
   
void Menu::printMenu () const{
    cout << "######################### Menu #########################" << endl;
    cout << "1 - Mostrar promoções mais recentes " << endl;
    cout << "2 - Mostrar promoções do forum Hardmob" << endl;
    cout << "3 - Mostrar promoções do forum Adrenaline" << endl;
    cout << "4 - Pesquisar promocoes por nome de produto " << endl;
    cout << "5 - Pesquisar promocoes por loja " << endl;
    cout << "6 - Pesquisar promocoes por preco " << endl;
    cout << "7 - Mostar Loja com mais promoções" << endl;
    cout << "0 - Sair do programa" << endl;
    cout << "######################### Menu #########################" << endl;
}


void Menu:: askMenuOption(){
    cout << "Escolha sua opcao : ";
    cin >> menuOption;
    while ( cin.fail() || menuOption > 7 || menuOption< 0){
        cout << "Opcao invalida. Escolha uma opcao entre 0 e 7 :" ;
        cin.clear(); // clears cin fail flag
        cin.ignore(1000,'\n'); // clear in stream
        cin >> menuOption;
    }
}

int Menu::getMenuOption() const {
    return menuOption;   
}


