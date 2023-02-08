#include "EmptyCircBuffer.h"
#include "jack_module.h"
#include "sawtooth.h"
#include "delay.h"

#include <iostream>
#include <cmath>
#include <unistd.h>
#include <array>
#include <iostream>


class Callback : public AudioCallback {

public:

    void prepare (int sampleRate) override {
        for (Delay& delay : delays)
        {
            delay.prepareToPlay(sampleRate);
        }
    }

    void process (AudioBuffer buffer) override {
        auto [inputChannels, outputChannels, numInputChannels, numOutputChannels, numFrames] = buffer;
        
        for (int channel = 0u; channel < numOutputChannels; ++channel) {
            for (int sample = 0u; sample < numFrames; ++sample) {
                delays[channel].input(inputChannels[channel][sample]);
                outputChannels[channel][sample] = delays[channel].output();
                // std::cout << delays[channel].output() << std::endl;
            }
        }
    }

    std::array<Delay, 2> delays;

private:
    Sawtooth saw = Sawtooth(500, 0.5f);
    
};


int main() {

    auto callback = Callback {};
    auto jack = JackModule (callback);

    // start jack client with 2 inputs and 2 outputs
    jack.init (2, 2);

    bool running = true;
    while (running) {
        switch (std::cin.get()) {
            case 'q':
                running = false;
                break;
        }
    }

    return 0;
}