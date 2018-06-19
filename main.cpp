#include "Base64.h"
#include "TwitterHandler.h"
#include<string>
#include<iostream>
#include<fstream>
#include "include/json.hpp"


using namespace std;
using Json = nlohmann::json;


void WritePromoFile(string jsonStr)
{
    ofstream myFile;
    myFile.open("posts.txt");

    Json json  = Json::parse(jsonStr);
    int size = json["statuses"].size();
    for(int i =0;i < size;i++){
        myFile << i << " " << json["statuses"][i]["text"] << endl;
    }   
    myFile.close();
}

int main()
{
    string consumerKey = "idNDUtlKDmWG0TPC0Hnp9MQmJ";  
    string consumerSecret = "MIL5EPvTickAVPifHXgsEfIBOnskatFIEooiWZZBjMrvLMVSsw";
    TwitterHandler twitterHandler;

    Json accessTokenJSON = Json::parse(twitterHandler.GetAccessToken(consumerKey,consumerSecret));
    string accessToken = accessTokenJSON["access_token"];


    cout << accessToken << endl;
    WritePromoFile((twitterHandler.GetTweets(accessToken)));

    return 0;
}