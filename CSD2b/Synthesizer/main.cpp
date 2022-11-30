#include <iostream>
#include <thread>
#include <fstream>
#include "jack_module.h"
#include "math.h"
#include "sine.h"
#include "square.h"
#include "sawtooth.h"
#include "melGen.h"

#define SOUND 1
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
      buffer.outputChannels[0][i] = saw.getSample();
      saw.process();
    }
  }
  private:
  float samplerate = 48000;
  Sine sine = Sine(500, 0.5);
  Square square = Square(500, 0.1);
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
      switch (std::cin.get()) {
          case 'q':
              running = false;
      }
  }

  #endif

  Sine sine1 = Sine(FREQ, 1.0);
  Square square1 = Square(FREQ, 1.0);
  Sawtooth saw1 = Sawtooth(FREQ, 1.0);

  std::ofstream audioFile;
  audioFile.open("output.csv");

  for(int i = 0; i < SAMPLERATE; i++)
  {
    audioFile << saw1.getSample() << std::endl;
    saw1.process();
  }

  audioFile.close();

  Melody melody1;

  for(int i = 0; i < NUM_NOTES; i++)
  {
      melody1.addNote(i + 69);
      std::cout << "Note: " << melody1.getNote(i) << std::endl;
  }

  int readPointer;
  std::cin >> readPointer;
  saw1.setFrequency(melody1.getNote(readPointer));


  //end the program
  return 0;
} // main()
