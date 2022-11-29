#include <iostream>
#include <thread>
#include "jack_module.h"
#include "math.h"
#include "sine.h"
#include "square.h"

/*
 * NOTE: jack2 needs to be installed
 * jackd invokes the JACK audio server daemon
 * https://github.com/jackaudio/jackaudio.github.com/wiki/jackd(1)
 * on mac, you can start the jack audio server daemon in the terminal:
 * jackd -d coreaudio
 */

class CustomCallback : public AudioCallback {
public:
  void prepare(int rate) override {
    samplerate = (float) rate;
    sine.setSamplerate(samplerate);
    std::cout << "\nsamplerate: " << samplerate << "\n";
  }

  void process(AudioBuffer buffer) override {
    for (int i = 0; i < buffer.numFrames; ++i) {
      // write sample to buffer at channel 0, amp = 0.25
      buffer.outputChannels[0][i] = square.getSample();
      square.process();
    }
  }
  private:
  float samplerate = 44100;
  Sine sine = Sine(500, 0.5, 0, 48000);
  Square square = Square(500, 0.1, 0, 48000);
};

int main(int argc,char **argv)
{
  auto callback = CustomCallback {};
  auto jackModule = JackModule { callback };

  jackModule.init (0, 1);

  bool running = true;
  while (running) {
      switch (std::cin.get()) {
          case 'q':
              running = false;
      }
  }

  //end the program
  return 0;
} // main()
