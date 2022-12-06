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

#define SOUND 1
#define WRITE_TO_FILE 1
#define FREQ 5

/*
 * NOTE: jack2 needs to be installed
 * jackd invokes the JACK audio server daemon
 * https://github.com/jackaudio/jackaudio.github.com/wiki/jackd(1)
 * on mac, you can start the jack audio server daemon in the terminal:
 * jackd -d coreaudio
 */


Melody melody1;
Timer timer1;

int readPointer = 0;
bool playing = true;

// void changeFreq() {
//     while (playing) {
//     timer1.start();
//     if (fmod(timer1.getTime(), 250) == 0)
//     {
//       sine.setFrequency(melody1.getNote(readPointer));
//       std::cout << "Freq: " << melody1.getNote(readPointer++) << std::endl;

//       if (readPointer == melody1.getSize())
//       {
//         readPointer = 0;
//       }
//     }
//   }
// }



int main(int argc,char **argv)
{

  melody1.addNote(10, 60, 80); //Amount of notes, minimum, maximum
  melody1.addNote(5, 90, 100);

  // thread changeNote(changeFreq);

  auto callback = CustomCallback {};
  auto jackModule = JackModule { callback };

  #if SOUND



  jackModule.init(0, 1);

  bool running = true;
  while (running) {
    }
      switch (std::cin.get()) {
          case 'q':
              running = false;
              playing = false;
      }

  // changeNote.join();

  #endif

  #if WRITE_TO_FILE

  AudioToFile audioFile = AudioToFile();
  audioFile.write(callback);

  #endif
  //end the program
  return 0;
} // main()
