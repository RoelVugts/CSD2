#include <iostream>

using namespace std;

class BankAccount {
    public:
        string currency;
        string name;

        BankAccount(int accountID)
        {
            balance = 0.0;
            this->accountID = accountID;
        }

        void setDetails();
        float deposit();
        float withdraw();
        void retrieveBalance();

        void getInfo();
        void showMenu();

        void setAccountID(int accountIDSet);
        int getAccountID();

    private:
        float balance;
        int accountID;

};