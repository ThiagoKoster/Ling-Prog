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
    cout << "5 - Promocoes do forum Hardmob" << endl;
    cout << "6 - Promocoes do forum Adrenaline" << endl;
    cout << "0 - Sair do programa" << endl;
    cout << "######################### Menu #########################" << endl;
}


void Menu::askMenuOption(){
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

void Menu::callFunction() const{
    string functionArgument;
    cin.ignore(1000,'\n'); // clear in stream
    switch(menuOption){
        case 0:
            cout << "Saindo do programa...." << endl;
            break;
        case 1:
            cout << "Quantas promocoes gostaria de visualizar? ";
            getline(cin,functionArgument);
            (*functions[menuOption-1])(functionArgument);
            break;
        case 2:
            cout << "Entre o produto a ser pesquisado : ";
            getline(cin,functionArgument);
            (*functions[menuOption-1])(functionArgument);
            break;
        case 3:
            cout << "Entre a loja a ser pesquisada : ";
            getline(cin,functionArgument);
            (*functions[menuOption-1])(functionArgument);
            break;
        case 4:
            cout << "Digite valor maximo: ";
            getline(cin,functionArgument);
            (*functions[menuOption-1])(functionArgument);
            break;
        case 5:
            cout << "Quantas promocoes Hardmob gostaria de visualizar? ";
            getline(cin,functionArgument);
            (*functions[menuOption-1])(functionArgument);
            break;
        case 6:
            cout << "Quantas promocoes do Adrenaline gostaria de visualizar? ";
            getline(cin,functionArgument);
            (*functions[menuOption-1])(functionArgument);
            break;
        default:
            break;
    }
}