#pragma once

#include "derived.h"
#include "derived2.h"

class Subderived : public Derived, Derived2 {
    public:
        Subderived();
    
    protected:
        int poep;
};