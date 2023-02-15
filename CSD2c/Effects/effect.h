//
// Created by Dean on 27/10/2022.
//
#pragma once

struct Effect {

    Effect() {}
    ~Effect() {}

    virtual void prepareToPlay (int samplerate) = 0;
    

    void setDryWet(float dryWet)
    {
        this->dryWet = dryWet;
    }

    protected:
        float dryWet { 1.0f };

};