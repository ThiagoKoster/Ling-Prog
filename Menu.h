class Menu{
    public:
        Menu(int item= -1) : choosedItem(item){}
         void printMenu();
         void askMenuOption();
         int getMenuOption();
    private:
         int choosedItem;

};