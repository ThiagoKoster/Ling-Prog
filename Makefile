################# Makefile #################
#### flags
CPP=g++
CPPFLAGS=-Wall -std=c++11
LFLAGS=-lcurl

#targets
MAIN = main.o Menu.o functions.o clearscreen.o TwitterHandler.o Base64.o
POSTS = posts.txt

main: $(MAIN)
	$(CPP) $(MAIN) -o main $(LFLAGS)



### files.o
main.o: main.cpp
	$(CPP) $(CPPFLAGS) -c main.cpp
TwitterHandler.o: TwitterHandler.cpp
	$(CPP) $(CPPFLAGS) -c TwitterHandler.cpp $(LFLAGS)

Base64.o: Base64.cpp
	$(CPP) $(CPPFLAGS) -c Base64.cpp

Menu.o : Menu.cpp
	$(CPP) $(CPPFLAGS) -c Menu.cpp
functions.o : functions.cpp
	$(CPP) $(CPPFLAGS) -c functions.cpp
clearscreen.o : clearscreen.cpp
	$(CPP) $(CPPFLAGS) -c clearscreen.cpp

clean:
	rm -rf *.o
	rm -rf main
	rm -rf $(POSTS)