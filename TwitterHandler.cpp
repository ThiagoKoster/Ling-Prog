#include "TwitterHandler.h"
#include "curl/curl.h"
#include "Base64.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

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

string TwitterHandler::GetAccessToken(string key,string secret)
{
    string strToEncode =  (key + ":" + secret).c_str();
    const unsigned int lenght = key.length() + secret.length() + 1;
    

    string basicAuth = base64_encode((const unsigned char*) strToEncode.c_str(),lenght);
    const char* headerParam = convert("Authorization: Basic " + basicAuth);

    struct curl_slist *headers=NULL; // init to NULL is important 
    headers = curl_slist_append(headers, headerParam);  
    headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded;charset=UTF-8");
    CURL *curl = curl_easy_init();

    string readBuffer;

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
    return readBuffer;
}

string TwitterHandler::GetTweets(string accessToken)
{
    struct curl_slist *headers=NULL; // init to NULL is important 
    string readBuffer;

    
    const char* headerParam = convert("Authorization: Bearer " + accessToken);
    headers = curl_slist_append(headers,headerParam);

    CURL *curl = curl_easy_init();
    if(curl) {
      
    
    curl_easy_setopt(curl, CURLOPT_URL, "https://api.twitter.com/1.1/search/tweets.json?q=from:hardmob_promo&count=100");

    
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

