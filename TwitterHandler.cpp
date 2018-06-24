#include "libs/TwitterHandler.h"
#include "libs/curl/curl.h"
#include "libs/Base64.h"
#include "libs/json.hpp"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include<fstream>
using namespace std;
using Json = nlohmann::json;

string TwitterHandler::_accessToken;

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

 char* convert(const std::string& str) {
    char* result = new char[str.length()+1];
    strcpy(result,str.c_str());
    return result;
}


 void TwitterHandler::WritePromoFile(string jsonStr, int mode, int startIndex)
{
    ofstream myFile;
   if(mode == 0)
   {
       myFile.open(filename);
   }
   else{
        myFile.open(filename,ios_base::app);
   }
      
    Json json  = Json::parse(jsonStr);
    int size = json["statuses"].size();
    for(int i = 0;i < size;i++){
        myFile << i + startIndex << " " << json["statuses"][i]["text"] << endl;
    }   
    myFile.close();
}

void TwitterHandler::ReadTweets(int max)
{
    ifstream myfile(filename);
    string line;
    int index = 0;
    while(getline(myfile,line))
    {
        if (index < max){
            cout << line << endl;
            index++;
        }
        else{
            return;
        }
        
    }
}

TwitterHandler::TwitterHandler(string key, string secret)
{
    Json accessTokenJSON = Json::parse(GetAccessToken(key,secret));
    TwitterHandler::_accessToken = accessTokenJSON["access_token"];
}

string TwitterHandler::GetAccessToken(string key,string secret)
{
    string strToEncode =  (key + ":" + secret).c_str();
    const unsigned int lenght = key.length() + secret.length() + 1;
    

    string basicAuth = base64_encode((const unsigned char*) strToEncode.c_str(),lenght);
    const char* headerParam = convert("Authorization: Basic " + basicAuth);

    struct curl_slist *headers=NULL; // init to NULL is important 
    headers = curl_slist_append(headers, headerParam);  
    headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded;charset=UTF-8");
    

    string readBuffer;
    _curl = curl_easy_init();
    if(_curl){
        curl_easy_setopt(_curl,CURLOPT_URL,"https://api.twitter.com/oauth2/token");
        curl_easy_setopt(_curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(_curl, CURLOPT_POSTFIELDS, "grant_type=client_credentials");
        curl_easy_setopt(_curl, CURLOPT_POST, 1);
        curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(_curl, CURLOPT_WRITEDATA, &readBuffer);
        readBuffer.clear();       
        curl_easy_perform(_curl);
    }
    curl_easy_cleanup(_curl);
    curl_slist_free_all(headers);
    return readBuffer;
}

string TwitterHandler::GetTweetsFromUser(int storeCode, string numberOfTweets = "100")
{
    struct curl_slist *headers=NULL; // init to NULL is important 
    string readBuffer;
    string storeTwitter = "";
    switch(storeCode){
        case 1:
            storeTwitter = "adrenaline_sale";
            break;
        default:
            storeTwitter = "hardmob_promo";
    }
   
    const char * URL = convert(
        "https://api.twitter.com/1.1/search/tweets.json?q=from:" + storeTwitter + 
        "&count=" + numberOfTweets);
    const char* headerParam = convert("Authorization: Bearer " + _accessToken);
    headers = curl_slist_append(headers,headerParam);

    _curl = curl_easy_init();
    if(_curl) {
        
    curl_easy_setopt(_curl, CURLOPT_URL, URL); 
    curl_easy_setopt(_curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(_curl, CURLOPT_HTTPGET,1);
    readBuffer.clear();
    curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(_curl, CURLOPT_WRITEDATA, &readBuffer);
    curl_easy_perform(_curl);
    
    }
      
    curl_easy_cleanup(_curl);
    curl_slist_free_all(headers);

    return readBuffer;
}

void TwitterHandler::WriteAllTweets()
{
    string hardMobTweets;
    string adrenTweets;

    hardMobTweets = GetTweetsFromUser(0);
    adrenTweets = GetTweetsFromUser(1);
    
    WritePromoFile(hardMobTweets); 
    WritePromoFile(adrenTweets,1,100); 
}


