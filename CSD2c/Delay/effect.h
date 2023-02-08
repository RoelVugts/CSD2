//
// Created by Dean on 27/10/2022.
//
#pragma once

struct Effect {
    virtual void prepareToPlay (int samplerate) = 0;
    virtual float input (float input) = 0;
};