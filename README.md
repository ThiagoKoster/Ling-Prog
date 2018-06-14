# Ling-Prog
Repo for Ling-Prog

#Installed Modules
Text::Table

Possible to-dos ? 
0 - Modularize Code
1 - Function to treat prices not in R$ XXX.XX,XX format
2 - Function to exclude words before price
3 - Function to replace incorrect store names
4 - See how to show installed modules


#IMPORTANT
Create "keys.txt" file in the project folder with the values of your ConsumerKey,ConsumerSecret,OAuthAccessTokenKey and OAuthAccessTokenSecret each at one line
To compile use "g++ -Wall main.cpp -o main -ltwitcurl"

#Instalation of twitcurl
Download libcurl https://curl.haxx.se/download.html. 
Install source code with the commands:
./configure --with-ssl
make
sudo make install

Download twitcurl : https://github.com/swatkat/twitcurl

