#include <iostream>
#include <iomanip>
#include <string>
#include "libs/Menu.h"
#include "libs/TwitterHandler.h"
#include "libs/PerlToCpp.h"

using namespace std;

static const string consumerKey = "idNDUtlKDmWG0TPC0Hnp9MQmJ";  
static const string consumerSecret = "MIL5EPvTickAVPifHXgsEfIBOnskatFIEooiWZZBjMrvLMVSsw";
 
   
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

void Menu::callFunction() const{

    string functionArgument;
    TwitterHandler twitterHandler(consumerKey,consumerSecret);
    

    cin.ignore(1000,'\n'); // clear in stream
    if(menuOption == 2)
    {
        cout << "Entre o produto a ser pesquisado : ";
        getline(cin,functionArgument);

        PerlToCpp perlToCpp("");
        perlToCpp.Interpreter(); 

        string out = perlToCpp.HelloWorld("helloWorld");           
        cout << out << endl;
    }
    // switch(menuOption){
    //     case 0:
    //         cout << "Saindo do programa...." << endl;
    //         break;
    //     case 1:
    //         cout << "Quantas promocoes gostaria de visualizar? ";
    //         getline(cin,functionArgument);
    //         twitterHandler.WriteAllTweets(functionArgument);
    //         cout << "Ultimas " << functionArgument << " promocoes : "<< endl;
    //         twitterHandler.ReadTweets(stoi(functionArgument));
    //         break;
    //     case 2:
    //         cout << "Entre o produto a ser pesquisado : ";
    //         getline(cin,functionArgument);
    //         PerlToCpp perlToCpp("");
    //         perlToCpp.Interpreter();            
    //         cout << perlToCpp.HelloWorld("helloWorld") << endl;
    //         break;
    //     case 3:
    //         cout << "Entre a loja a ser pesquisada : ";
    //         getline(cin,functionArgument);
           
    //         break;
    //     case 4:
    //         cout << "Digite valor maximo: ";
    //         getline(cin,functionArgument);
            
    //         break;
    //     case 5:
    //         cout << "Quantas promocoes Hardmob gostaria de visualizar? ";
    //         getline(cin,functionArgument);
    //         twitterHandler.WritePromoFile(twitterHandler.GetTweetsFromUser(0,functionArgument));
    //         cout << "Ultimas "<< functionArgument << " promocoes do forum Hardmob : " << endl;
    //         twitterHandler.ReadTweets();
    //         break;
    //     case 6:
    //         cout << "Quantas promocoes do Adrenaline gostaria de visualizar? ";
    //         getline(cin,functionArgument);
    //         twitterHandler.WritePromoFile(twitterHandler.GetTweetsFromUser(1,functionArgument));
    //         cout << "Ultimas "<< functionArgument << " promocoes do forum Adrenaline : " << endl;
    //         twitterHandler.ReadTweets();
    //         break;
    //     default:
    //         break;
    // }
}