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

  int synthChoice = askQuestion("What synth you want to play?", {"FmSynth", "SuperSynth"}, false, 15);
  

  
  float carrierFreq = 0;
  float carrierAmp = 0;
  float modulatorFreq = 0;
  float modulatorAmp = 0;
  int waveform = 0;

  int note;
  int amplitude;
  int numVoices;
  int detunePercentage;

  if (synthChoice == 0) {
    carrierFreq = askQuestion("What should be the frequency for the carrier?", 20, 20000);
    carrierAmp = askQuestion("What should be the amplitude of the carrier?", 0.0, 1.0);
    modulatorFreq = askQuestion("What should be the frequency for the modulator?", 1, 20000);
    modulatorAmp = askQuestion("What should be the amplitude of the modulator?", 0.0, 1.0);\
    waveform = askQuestion("What should be the waveform of the modulator?", {"Sine", "Square", "Saw"}, false, 15);
  } else if (synthChoice == 1) {
      note = askQuestion("What note do you want the synth to play", 24, 96);
      amplitude = askQuestion("What amplitude do you want thet synth to play?", 0.0, 1.0);
      numVoices = askQuestion("How many voices do you want?", 1, 6);
      detunePercentage = askQuestion("How much detune do you want? (0 - 100%)", 0, 100);
  }


  Synth* synths[2]= {new FmSynth(carrierFreq, carrierAmp, waveform, modulatorFreq, modulatorAmp), new SuperSynth(note, amplitude, numVoices, detunePercentage)};

  Synth* chosenSynth = synths[synthChoice];

  bool playMelody;
  playMelody = askQuestion("Do you want to play a melody?");

  Melody melody = Melody();
  melody.addNote(32);

  auto callback = CustomCallback {};
  auto jackModule = JackModule { callback };

  callback.setSynth(chosenSynth);
  
  jackModule.init(0, 1);


  bool running = true;
  if (playMelody) {
    melody.play(200, chosenSynth);
  }

  
  // callback.synth.setLFO("Sine", 1, 1.0);

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
