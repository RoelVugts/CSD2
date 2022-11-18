#include <iostream>

#include "bank.h"

using namespace std;


int main() {

    BankAccount myAccount(89826384);
    
    myAccount.setDetails();
    myAccount.showMenu();

    return 0;
};