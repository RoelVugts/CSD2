//
// Created by Dean on 27/10/2022.
//
#pragma once

struct Effect {

    Effect() {}
    ~Effect() {}

    virtual void prepareToPlay (int samplerate) = 0;
    virtual float output(float input) = 0;

    void setDryWet(float dryWet)
    {
        if (dryWet > 1.0f)
            this->dryWet = 1.0f;
        else if (dryWet < 0.0f)
            this->dryWet = 0.0f;
        else
            this->dryWet = dryWet;
    }

    protected:
        float dryWet { 1.0f };

};