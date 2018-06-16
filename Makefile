################# Makefile #################
#### flags
CPP=g++
CPPFLAGS=-Wall
MAIN_MENU = main_menu.o Menu.o functions.o clearscreen.o

main_menu: $(MAIN_MENU)
	$(CPP) $(MAIN_MENU) -o main_menu

### files.o
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