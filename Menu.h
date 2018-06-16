#include "functions.h"

class Menu{
    public:
        Menu(int option= -1) : menuOption(option){}
        void printMenu() const;
        int getMenuOption() const;
        void askMenuOption();
        void callFunction() const;        
    private:
        int menuOption;
        void (*functions[6])(int) = {exitProgram,f1,f2,f3,f4,f5};

};