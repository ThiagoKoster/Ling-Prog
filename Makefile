################# Makefile #################
#### flags
CPP=g++
CPPFLAGS=-Wall -std=c++11
LFLAGS=-lcurl

#targets
MAIN = main.o TwitterHandler.o Base64.o
MAIN_MENU = main_menu.o Menu.o functions.o clearscreen.o
POSTS = posts.txt

main: $(MAIN)
	$(CPP) $(MAIN) -o main $(LFLAGS)

main_menu: $(MAIN_MENU)
	$(CPP) $(MAIN_MENU) -o main_menu

### files.o
main.o: main.cpp
	$(CPP) $(CPPFLAGS) -c main.cpp
TwitterHandler.o: TwitterHandler.cpp
	$(CPP) $(CPPFLAGS) -c TwitterHandler.cpp $(LFLAGS)
Base64.o: Base64.cpp
	$(CPP) $(CPPFLAGS) -c Base64.cpp

main_menu.o: main_menu.cpp
	$(CPP) $(CPPFLAGS) -c main_menu.cpp
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