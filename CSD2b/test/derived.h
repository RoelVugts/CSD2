#pragma once

#include "base.h"

class Derived : virtual public Base {
    public:
        Derived();

    protected:
        int derMember;
};