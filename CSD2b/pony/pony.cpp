#include "pony.h"

float Pony::calculatePrice(float marketPrice) {
    Pony::price = (Pony::speed / Pony::age) * 1000 * marketPrice;
    return Pony::price;
};

void Pony::run() {
    cout << "Running at " << Pony::speed << "Km/h!" << endl; 
};

