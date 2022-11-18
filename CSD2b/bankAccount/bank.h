#include <iostream>

using namespace std;

class BankAccount {
    public:
        int accountID;
        string currency;
        float balance;
        string name;

        BankAccount(int id)
        {
            balance = 0.0;
            accountID = id;
        }

        void setDetails();
        float deposit();
        float withdraw();
        void retrieveBalance();

        void getInfo();
        void showMenu();

};