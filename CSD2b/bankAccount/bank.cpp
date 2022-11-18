#include <iostream>

#include "bank.h"

using namespace std;

void BankAccount::setDetails() {
    cout << "Please enter your name: ";
    getline(cin, BankAccount::name);
    cout << "Please enter currency: ";
    cin >> BankAccount::currency;
    cout << "\n";
    cout << "Hi " << BankAccount::name << "\n" << endl;
};

float BankAccount::deposit() {
    float amount;
    cout << "Enter amount: ";
    cin >> amount;
    cout << endl;
    BankAccount::balance += amount;
    return BankAccount::balance;
};

float BankAccount::withdraw() {
    float amount;
    cout << "Enter amount: ";
    cin >> amount;
    cout << endl;
    BankAccount::balance -= amount;
    return BankAccount::balance;
};

void BankAccount::retrieveBalance() {
    cout << "Currenct Balance: " << BankAccount::balance << " " + BankAccount::currency << "\n" << endl;
};

void BankAccount::getInfo() {
    int userChoice;
    cout << "What would you like to know?" << endl;
    cout << "1 = Account ID" << endl;
    cout << "2 = Currency" << endl;
    cout << "3 = Balance" << "\n" << endl;
    cin >> userChoice;

    switch(userChoice) 
    {
        case 1: cout << "Account ID: " << BankAccount::accountID << endl;
        break;
        case 2: cout << "Currency: " << BankAccount::currency << endl;
        break;
        case 3: cout << "Balance: " << BankAccount::balance << endl;
    };

};

void BankAccount::showMenu() {
    int userInput;

    while (true) {
        cout << "Bank Menu\n1 = Deposit\n2 = Withdraw\n3 = Info\n4 = Exit\n" << endl;
        cin >> userInput;
    
        switch(userInput) {
            case 1: deposit();
            continue;
            case 2: withdraw();
            continue;
            case 3: getInfo();
            continue;
            case 4: break;
        }
        break;
    };
}