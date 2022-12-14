#include <iostream>
#include <thread>
#include <fstream>
#include <cmath>
#include <thread>
#include <algorithm>

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
#include "FmSynth.h"
#include "UI.h"

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

  askQuestion("What synth you want to play?", {"FmSynth", "SuperSynth"}, false, 15);



  Melody melody = Melody();
  melody.addNote(32);

  for(int i = 0; i < melody.getSize(); i++)
  {
    // std::cout << "Note: " << i << melody.notes[i] << std::endl;
    // std::cout << "Freq: " << i << melody.getNote(i) << std::endl;
  }

  auto callback = CustomCallback {};
  auto jackModule = JackModule { callback };
  
  jackModule.init(0, 1);


  bool running = true;
  
  melody.play(200, &callback.fmSynth);
  callback.fmSynth.setLFO("Square", 0.1, 5.0);

  while (running) {
      switch (std::cin.get()) {
          case 'q':
              melody.stop();
              running = false;    
      }
  }

  AudioToFile audioFile = AudioToFile();
  audioFile.write(callback);

  //end the program
  return 0;
} // main()
