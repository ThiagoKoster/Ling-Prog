#include <iostream>
#include <string>
#include "functions.h"

using namespace std;

void showRecentPromotions(string num){
    cout << "Ultimas " << num << " promocoes : "<< endl;
}

void searchProduct(string product){
    cout << "Promocoes contendo produto -"<< product << "- encontadas: " << endl;
}

void searchStore(string store){
    cout << "Promocoes na loja -"<< store << "- encontradas: " << endl;
}

void searchPrice(string maxPrice){
    cout << "Promocoes com valor maximo de "<< maxPrice<<" : " << endl;
}

void showHardmob(string num){
    cout << "Ultimas "<< num << " promocoes do forum Hardmob : " << endl;
}

void showAdrenaline(string num){
    cout << "Ultimas "<< num << " promocoes do forum Adrenaline : " << endl;
}