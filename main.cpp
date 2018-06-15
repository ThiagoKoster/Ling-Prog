#include "Base64.h"
#include<string>
#include<iostream>
#include<curl/curl.h>
#include <json.hpp>
#include <algorithm>
using namespace std;
using std::replace;
using Json = nlohmann::json;

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

string GetAccessToken(string key,string secret)
{
     string strToEncode =  (key + ":" + secret).c_str();
    const unsigned int lenght = key.length() + secret.length() + 1;
    

    string basicAuth = base64_encode((const unsigned char*) strToEncode.c_str(),lenght);
    const char* headerParam = ("Authorization: Basic " + basicAuth).c_str();
    struct curl_slist *headers=NULL; // init to NULL is important 
    headers = curl_slist_append(headers, headerParam);  
    headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded;charset=UTF-8");
    CURL *curl = curl_easy_init();

    string readBuffer;
    Json outputJson;
    if(curl){
        curl_easy_setopt(curl,CURLOPT_URL,"https://api.twitter.com/oauth2/token");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "grant_type=client_credentials");
        curl_easy_setopt(curl, CURLOPT_POST, 1);
        readBuffer.clear();
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        
        curl_easy_perform(curl);
    }
    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);
    headerParam = nullptr;
    return readBuffer;
}

string GetTweets(string accessToken)
{
    struct curl_slist *headers=NULL; // init to NULL is important 
    CURL *curl = curl_easy_init();

    string readBuffer;
    Json outputJson;
    
    
    if(curl) {
    //cout << headerParam << endl;
    headers = curl_slist_append(headers, "Authorization: Bearer AAAAAAAAAAAAAAAAAAAAAB5b6gAAAAAAa%2FiLGU3x5csgAxNoDdU%2BrULystQ%3DJT8UqfSNd8gZq5DSil93IT4UTvn7dbqVKYokLu5VJdJvK1V9gi"); 
    
    //TODO: POR ALGUM MOTIVO USANDO headerParam NÃO FUNCIONA...
    //const char* headerParam = ("Authorization: Bearer " + accessToken).c_str();
    //headers = curl_slist_append(headers,headerParam); 
    
    curl_easy_setopt(curl, CURLOPT_URL, "https://api.twitter.com/1.1/search/tweets.json?q=nasa&result_type=popular");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_HTTPGET,1);
    readBuffer.clear();
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    curl_easy_perform(curl);
    
    }
      
    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);
    return readBuffer;
}

int main()
{
    string consumerKey = "idNDUtlKDmWG0TPC0Hnp9MQmJ";  
    string consumerSecret = "MIL5EPvTickAVPifHXgsEfIBOnskatFIEooiWZZBjMrvLMVSsw";
       
    Json accessTokenJSON = Json::parse(GetAccessToken(consumerKey,consumerSecret));
    string accessToken = accessTokenJSON["access_token"];

    //Remover \" da string
    accessToken.erase(std::remove(accessToken.begin(), accessToken.end(), '\"'), accessToken.end());

    cout << accessToken << endl;
    Json tweets = Json::parse(GetTweets(accessToken));

    cout << tweets << endl;
    
   
    return 0;
}