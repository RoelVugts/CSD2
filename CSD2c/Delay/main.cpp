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
    
};


int main() {

    auto callback = Callback {};
    auto jack = JackModule (callback);

    // start jack client with 2 inputs and 2 outputs
    jack.init (2, 2);

    bool running = true;
    std::cout << "b = set new buffer size\nd = set new delay time\ns = get current buffer size\nt = get current delay time\nq= exit" << std::endl;
    while (running) {
        switch (std::cin.get()) {
            case 'q':
                running = false;
                break;
            case 'b':
                int maxDelay;
                std::cout << "Enter new buffer size (ms): ";
                std::cin >> maxDelay;
                for (Delay& delay : callback.delays)
                    delay.setMaxDelay(maxDelay);
                std::cout << "Set max delay to: " << maxDelay << " ms" << std::endl;
                continue;
            case 's':
                for (Delay& delay : callback.delays)
                    std::cout << "Current max delay: " << delay.circBuf.getSize() << std::endl;
                continue;
            case 'd':
                int delayTime;
                std::cout << "Enter new delay time (ms): ";
                std::cin >> delayTime;
                for (Delay& delay : callback.delays)
                    delay.setDelayTime(delayTime);
                std::cout << "Set delay time to: " << delayTime << " ms" << std::endl;
                continue;
            case 't':
                    std::cout << "Current delay time: " << callback.delays[1].getDelayTime() << std::endl;
                    std::cout << "readHead: " << callback.delays[1].circBuf.getReadPosition() << std::endl;
                    std::cout << "writeHead: " << callback.delays[1].circBuf.getWritePosition() << std::endl;
                    std::cout << "writeMax: " << callback.delays[1].circBuf.writeMax << std::endl;
                    std::cout << "readMax: " << callback.delays[1].circBuf.readMax << std::endl;
                    std::cout << "Current max delay: " << callback.delays[1].circBuf.getSize() << std::endl;
                    std::cout << "delayStarted: " << callback.delays[1].circBuf.delayStarted << std::endl;

        }
    }

    return 0;
}