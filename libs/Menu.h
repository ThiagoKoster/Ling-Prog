#include <string>

class Menu{
    public:
        Menu(int option= -1) : menuOption(option){}
        void printMenu() const;
        int getMenuOption() const;
        void askMenuOption();       
    private:
        int menuOption;
        
};