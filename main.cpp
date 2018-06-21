#include <iostream>
#include<string>

#include "libs/PerlToCpp.h"
#include "libs/Menu.h"
#include "libs/clearscreen.h"
#include "libs/TwitterHandler.h"

using namespace std;

static const string consumerKey = "idNDUtlKDmWG0TPC0Hnp9MQmJ";  
static const string consumerSecret = "MIL5EPvTickAVPifHXgsEfIBOnskatFIEooiWZZBjMrvLMVSsw";

int main(void)
{ 
    Menu menu;
    TwitterHandler twitterHandler(consumerKey,consumerSecret);
    PerlToCpp perl("");
    perl.Interpreter();
    string functionArgument;
    twitterHandler.WriteAllTweets("30");

    //clearScreen();
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
                twitterHandler.WriteAllTweets(functionArgument);
                cout << "Ultimas " << functionArgument << " promocoes : "<< endl;
                twitterHandler.ReadTweets(stoi(functionArgument));
                break;
            case 2:
                cout << "Entre o produto a ser pesquisado : ";
                getline(cin,functionArgument);
                cout << perl.searchProduct(functionArgument) << endl;           
                break;
            case 3:
                cout << "Entre a loja a ser pesquisada : ";
                getline(cin,functionArgument);
                cout << perl.searchStore(functionArgument) << endl;
                break;
            case 4:
                cout << "Digite valor maximo: ";
                getline(cin,functionArgument);
                
                break;
            case 5:
                cout << "Quantas promocoes Hardmob gostaria de visualizar? ";
                getline(cin,functionArgument);
                twitterHandler.WritePromoFile(twitterHandler.GetTweetsFromUser(0,functionArgument));
                cout << "Ultimas "<< functionArgument << " promocoes do forum Hardmob : " << endl;
                twitterHandler.ReadTweets();
                break;
            case 6:
                cout << "Quantas promocoes do Adrenaline gostaria de visualizar? ";
                getline(cin,functionArgument);
                twitterHandler.WritePromoFile(twitterHandler.GetTweetsFromUser(1,functionArgument));
                cout << "Ultimas "<< functionArgument << " promocoes do forum Adrenaline : " << endl;
                twitterHandler.ReadTweets();
                break;
            default:
                break;
        }
        
        cout << "Pressione ENTER para continuar";
        cin.get(); // press enter to continue
        clearScreen();
    }

    return 0;
}