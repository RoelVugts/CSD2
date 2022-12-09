#include <iostream>
#include <thread>
#include <fstream>
#include <cmath>
#include <thread>
#include "jack_module.h"
#include "math.h"
#include "sine.h"
#include "square.h"
#include "sawtooth.h"
#include "melGen.h"
#include "timer.h"
#include "callback.h"
#include "audioToFile.h"
#include "antiAliasedSquare.h"
#include "antiAliasedOsc.h"
#include "antiAliasedSaw.h"

#define SOUND 0
#define WRITE_TO_FILE 1
#define FREQ 5

/*
 * NOTE: jack2 needs to be installed
 * jackd invokes the JACK audio server daemon
 * https://github.com/jackaudio/jackaudio.github.com/wiki/jackd(1)
 * on mac, you can start the jack audio server daemon in the terminal:
 * jackd -d coreaudio
 */

int main(int argc,char **argv)
{

  // Melody melody = Melody();
  // melody.addNote(8);

  auto callback = CustomCallback {};
  auto jackModule = JackModule { callback };
  
  jackModule.init(0, 1);
  bool playing = true;
  
  // while (playing) {
  //   melody.play(200, &(callback.aSaw));
  // }

  bool running = true;
  while (running) {
      switch (std::cin.get()) {
          case 'q':
              running = false;
              playing = false;
              
      }
  }

  AudioToFile audioFile = AudioToFile();
  audioFile.write(callback);

  //end the program
  return 0;
} // main()
