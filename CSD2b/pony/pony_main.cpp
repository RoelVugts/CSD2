#include "pony.h"

using namespace std;

int main() {

    Pony myPony(2.54, "purd", 45, 12);
    Pony myLittlePony(1.76, "shetlander", 22, 4);

    cout << "Pony Price: " << myLittlePony.calculatePrice(1.5) << endl;
    cout << "Pony Price: " << myPony.calculatePrice(0.2) << endl;

    myLittlePony.run();
    myPony.run();

    return 0;
}