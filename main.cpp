#include <iostream>
#include <fstream>
#include<string>

#include "libs/PerlToCpp.h"
#include "libs/Menu.h"
#include "libs/clearscreen.h"
#include "libs/TwitterHandler.h"

using namespace std;

static const string consumerKey = "use your consumerKey here";  
static const string consumerSecret = "use your consumerSecret here";

bool onlyDigits(const string &str){
    for(unsigned i = 0;i < str.length();i++){
        if(!isdigit(str[i])){
            return false;
        }
    }
    return true;
}
void printFile(string fileName)
{
    ifstream f(fileName);
    if (f.is_open())
        std::cout << f.rdbuf();
}

bool checkInput(string &input){
    while(!onlyDigits(input)){  //The input is valid?
        cout << "Numero invalido, entre com apenas digitos. Tente novamente ou entre com \"exit\" para ir ao menu: ";
        getline(cin,input);
        if(input == "exit"){
            return false;
        }
    }
    return true;
}

int main(void)
{ 
    Menu menu;
    TwitterHandler twitterHandler(consumerKey,consumerSecret);
    PerlToCpp perl("");
    perl.Interpreter();
    
    string functionArgument;
    string minPrice;
    string maxPrice;
    string storeName;

    cout << "Carregando Promocoes..." << endl;
    twitterHandler.WriteAllTweets();

    clearScreen();
    
    while( menu.getMenuOption() != 0){
        menu.printMenu();
        menu.askMenuOption();
        cin.ignore(1000,'\n'); // clear in stream
        switch(menu.getMenuOption()){
            case 0:
                cout << "Saindo do programa...." << endl;
                break;
            case 1:
                cout << "Quantas promocoes gostaria de visualizar? ";
                getline(cin,functionArgument);
                if(checkInput(functionArgument)){
                    twitterHandler.WriteAllTweets();
                    cout << "Ultimas " << functionArgument << " promocoes : "<< endl;
                    twitterHandler.ReadTweets(stoi(functionArgument));
                    twitterHandler.WriteAllTweets();
                }              
                break;
            case 2:
                cout << "Quantas promocoes Hardmob gostaria de visualizar? ";
                getline(cin,functionArgument);
                if(checkInput(functionArgument)){
                    twitterHandler.WritePromoFile(twitterHandler.GetTweetsFromUser(0,functionArgument));
                    cout << "Ultimas "<< functionArgument << " promocoes do forum Hardmob : " << endl;
                    twitterHandler.ReadTweets();
                    twitterHandler.WriteAllTweets();
                }
               
                break;
            case 3:
                cout << "Quantas promocoes do Adrenaline gostaria de visualizar? ";
                getline(cin,functionArgument);
                if(checkInput(functionArgument)){
                    twitterHandler.WritePromoFile(twitterHandler.GetTweetsFromUser(1,functionArgument));
                    cout << "Ultimas "<< functionArgument << " promocoes do forum Adrenaline : " << endl;
                    twitterHandler.ReadTweets();
                    twitterHandler.WriteAllTweets();
                }    
                break;           
            case 4:
                cout << "Entre o produto a ser pesquisado : ";
                getline(cin,functionArgument);
                printFile( perl.searchProduct(functionArgument));           
                break;
            case 5:
                cout << "Entre a loja a ser pesquisada : ";
                getline(cin,functionArgument);
                printFile( perl.searchStore(functionArgument));
                break;
            case 6:
                cout << "Digite valor minimo: ";
                getline(cin,minPrice);
                if(!checkInput(minPrice)){
                    break;
                }
                cout << "Digite valor maximo: ";
                getline(cin,maxPrice);
                if(!checkInput(maxPrice)){
                    break;
                }
                functionArgument = perl.searchPrice(minPrice,maxPrice);
                if ( functionArgument[0] == '0'){
                    cout << "Erro : Faixa de valores incorreta. Forneça valor minimo diferente e menor do que valor maximo" << endl;
                }
                else{
                    printFile(functionArgument);           
                }              
                break;            
            case 7:
                functionArgument = perl.searchStoreWithMorePromotions();
                storeName = functionArgument.substr(0, functionArgument.find(' '));
                cout << "A Loja com mais promoções é : " << functionArgument << endl; 
                printFile( perl.searchStore(storeName));
            default:
                break;
        }
        
        cout << "Pressione ENTER para continuar";
        cin.get(); // press enter to continue
        clearScreen();
    }

    return 0;
}
