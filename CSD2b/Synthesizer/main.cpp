#include <iostream>
#include <thread>
#include <fstream>
#include "jack_module.h"
#include "math.h"
#include "sine.h"
#include "square.h"
#include "sawtooth.h"
#include "melGen.h"

#define SOUND 0
#define FREQ 5

/*
 * NOTE: jack2 needs to be installed
 * jackd invokes the JACK audio server daemon
 * https://github.com/jackaudio/jackaudio.github.com/wiki/jackd(1)
 * on mac, you can start the jack audio server daemon in the terminal:
 * jackd -d coreaudio
 */

#if SOUND

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
  float samplerate = 48000;
  Sine sine = Sine(500, 0.5);
  Square square = Square(FREQ, 0.1);
  Sawtooth saw = Sawtooth(500, 1.0);
};

#endif


int main(int argc,char **argv)
{


#if SOUND



  auto callback = CustomCallback {};
  auto jackModule = JackModule { callback };

  jackModule.init(0, 1);

  bool running = true;
  while (running) {
    }
      switch (std::cin.get()) {
          case 'q':
              running = false;
      }

#endif

  Sine sine1 = Sine(FREQ, 1.0);
  Square square1 = Square(FREQ, 1.0);
  Sawtooth saw1 = Sawtooth(FREQ, 1.0);
  Melody melody1;
  
  melody1.addNote(10, 60, 80); //Amount of notes, minimum, maximum
  melody1.addNote(5, 20, 30);

  for(int i = 0; i < melody1.getSize(); i++)
  {
    std::cout << "Note: " << melody1.getNote(i) << std::endl;
  }

  std::ofstream audioFile;
  audioFile.open("output.csv");
  int duration = 2;

  for(int i = 0; i < SAMPLERATE * duration; i++)
  {
    audioFile << square1.getSample() << std::endl;
    square1.process();
  }

  audioFile.close();



  //end the program
  return 0;
} // main()
