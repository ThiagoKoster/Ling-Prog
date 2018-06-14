#include<iostream>
#include<fstream>
#include<twitcurl.h>

using namespace std;

void getKeys(string &consumerK,string &consumerS,string &accessTokenK,string &accessTokenS )
{
    ifstream keysFile;
    string line;
    keysFile.open("keys.txt");
    getline(keysFile,consumerK);
    getline(keysFile,consumerS);
    getline(keysFile,accessTokenK);
    getline(keysFile,accessTokenS);
}

int main(int argc, char const *argv[])
{
 
  twitCurl twitter;
  string consumerKey ;
  string consumerSecret ;
  string myOAuthAccessTokenKey ;
  string myOAuthAccessTokenSecret;

  getKeys(consumerKey,consumerSecret,myOAuthAccessTokenKey,myOAuthAccessTokenSecret);
    cout << consumerKey << endl;
    cout << consumerSecret << endl;
    cout << myOAuthAccessTokenKey << endl;
    cout << myOAuthAccessTokenSecret << endl;

  twitter.getOAuth().setConsumerKey(consumerKey);
  twitter.getOAuth().setConsumerSecret(consumerSecret);
  twitter.getOAuth().setOAuthTokenKey(myOAuthAccessTokenKey);
  twitter.getOAuth().setOAuthTokenSecret(myOAuthAccessTokenSecret);

  string tweetTest = "Hello World!";
  string replyMsg;
  if(twitter.statusUpdate(tweetTest))
  {
    twitter.getLastWebResponse(replyMsg);
    printf("\ntwitterClient::twitcurl::statusUpdate web response:\n%s\n",replyMsg.c_str());
  }else{
    twitter.getLastCurlError(replyMsg);
    printf("\ntwitterClient::twitcurl::statusUpdate ERROR:\n%s\n",replyMsg.c_str());
  }

  return 0;
}
