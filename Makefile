################# Makefile #################
#### flags
CPP=g++
CPPFLAGS=-Wall -std=c++11 $(shell perl -MExtUtils::Embed -e ccopts -e ldopts)
LFLAGS=-lcurl $(shell perl -MExtUtils::Embed -e ldopts)

#targets
MAIN = main.o Menu.o  clearscreen.o TwitterHandler.o Base64.o PerlToCpp.o 
TEXTFILES = posts.txt priceRangePromotions.txt productPromotions.txt storePromotions.txt

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
clearscreen.o : clearscreen.cpp
	$(CPP) $(CPPFLAGS) -c clearscreen.cpp
PerlToCpp.o : PerlToCpp.cpp
	$(CPP) $(CPPFLAGS) -c PerlToCpp.cpp

clean:
	rm -rf *.o
	rm -rf main
	rm -rf $(TEXTFILES)