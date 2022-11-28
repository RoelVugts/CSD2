#include "base.h"
#include "derived.h"
#include "derived2.h"
#include "subderived.h"

int main() {
    

    Subderived synthKick;
    synthKick.setSound("Boem");
    synthKick.play();

    return 0;
}