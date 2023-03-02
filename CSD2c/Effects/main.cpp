#include "CircularBuffer.h"
#include "jack_module.h"
#include "delay.h"
#include "tremolo.h"
#include "waveshaper.h"
#include "sine.h"
#include "pitchShifter.h"
#include "filePlayer.h"
#include "chorus.h"
#include "sawtooth.h"
#include "flanger.h"
#include "triangle.h"
#include "filter.h"

#include <iostream>
#include <cmath>
#include <unistd.h>
#include <array>
#include <iostream>


class Callback : public AudioCallback {

public:

    void prepare (int sampleRate) override 
    {
        for (int i = 0; i < 2; i++)
        {
            delays[i].prepareToPlay(sampleRate);
            delays[i].setFeedback(0.5f);
            tremolos[i].prepareToPlay(sampleRate);
            waveshapers[i].prepareToPlay(sampleRate);
            pitchShifters[i].prepareToPlay(sampleRate);
            pitchShifters[i].setPitchNote(0.0f);
            sines[i].setSamplerate(sampleRate);
            flangers[i].prepareToPlay(sampleRate);
            flangers[i].setDryWet(0.5f);
            flangers[i].setFeedback(0.0f);
            saws[i].setSamplerate(sampleRate);
            triangles[i].setSamplerate(sampleRate);
        }

        chorus.prepareToPlay(sampleRate);
        chorus.setDryWet(0.5f);
        chorus.setFeedback(0.5f);
        
        vocal.open("ready.wav");

    }

    void process (AudioBuffer buffer) override {
        auto [inputChannels, outputChannels, numInputChannels, numOutputChannels, numFrames] = buffer;
        
        for (int channel = 0u; channel < numOutputChannels; ++channel) { 
            for (int sample = 0u; sample < numFrames; ++sample) 
            {
                sines[channel].tick();
                saws[channel].tick();
                triangles[channel].tick();
                // outputChannels[channel][sample] = delays[channel].output(inputChannels[channel][sample]);
                // outputChannels[channel][sample] = tremolos[channel].output(sines[channel].getSample());
                // outputChannels[channel][sample] = waveshapers[channel].output(sines[channel].getSample());
                // outputChannels[channel][sample] = pitchShifters[channel].output(inputChannels[channel][sample]);
                // outputChannels[channel][sample] = chorus.output(sines[channel].getSample(), channel);
                // outputChannels[channel][sample] = sines[channel].getSample();
                // outputChannels[channel][sample] = vocal.read(channel);
                // outputChannels[channel][sample] = flangers[channel].output(saws[channel].getSample());
                // outputChannels[channel][sample] = triangles[channel].getSample();
                outputChannels[channel][sample] = filters[channel].output(saws[channel].getSample());

            }
        }
    }

    std::array<Tremolo, 2> tremolos;
    std::array<Delay, 2> delays;
    std::array<Waveshaper, 2> waveshapers;
    std::array<PitchShifter, 2> pitchShifters;
    std::array<Flanger, 2> flangers;
    Chorus chorus;
    FilePlayer vocal;
    std::array<Sawtooth, 2> saws { Sawtooth(400, 0.8f), Sawtooth(400, 0.8f) };
    std::array<Triangle, 2> triangles { Triangle(400, 0.5f), Triangle(400, 0.5f) };
    std::array<Filter, 2> filters { Filter(), Filter() };


private:
    std::array<Sine, 2> sines { Sine(400, 0.5f), Sine(400, 0.5f) };
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
            case 'd':
                int delayTime;
                std::cout << "Enter new delay time (ms): ";
                std::cin >> delayTime;
                for (Delay& delay : callback.delays)
                    delay.setDelayTime(delayTime);
                std::cout << "Set delay time to: " << delayTime << " ms" << std::endl;
        }
    }

    return 0;
}