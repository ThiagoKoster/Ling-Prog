#include <iostream>
#include <string>
#include "libs/functions.h"
#include "libs/TwitterHandler.h"

using namespace std;

void searchProduct(string product){
    cout << "Promocoes contendo produto -"<< product << "- encontadas: " << endl;
}

void searchStore(string store){
    cout << "Promocoes na loja -"<< store << "- encontradas: " << endl;
}

void searchPrice(string maxPrice){
    cout << "Promocoes com valor maximo de "<< maxPrice<<" : " << endl;
}
