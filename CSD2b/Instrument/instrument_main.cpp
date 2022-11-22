#include <iostream>

#include "instrument.h"
#include "percussion.h"

using namespace std;

int main() {

    Percussion snare(5,6,7,8, "Snare");
    snare.showProperties();

    snare.setName("Henk");
    snare.setHarmStruct("Noisy");
    snare.setSound("Duummffff");
    cout << "\n";
    snare.showProperties();

    
    cout << "\n";
    return 0;
}