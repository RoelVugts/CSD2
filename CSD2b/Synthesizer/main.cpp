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
#include "env.h"

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
  
  //FmSynth properties
  float carrierFreq = 0;
  float carrierAmp = 0;
  float modulatorFreq = 0;
  float modulatorAmp = 0;
  int waveform = 0;

  //Supersynth properties
  int note = 60;
  float amplitude = 1.0;
  int numVoices = 3;
  int detunePercentage = 20;

  // Envelope env = Envelope();
  // env.trigger();
  // std::cout << "Drol: " << env.getLevel() << std::endl;

  if (synthChoice == 0) { //if user selects the FmSynth
    carrierFreq = askQuestion("What should be the frequency for the carrier?", 20, 20000);
    carrierAmp = askQuestion("What should be the amplitude of the carrier?", 0.0, 1.0);
    modulatorFreq = askQuestion("What should be the frequency for the modulator?", 1, 20000);
    modulatorAmp = askQuestion("What should be the amplitude of the modulator?", 0.0, 1.0);\
    waveform = askQuestion("What should be the waveform of the modulator?", {"Sine", "Square", "Saw"}, false, 15);
  } else if (synthChoice == 1) { //if user selects the superSynth
      note = askQuestion("What note do you want the synth to play?", 24, 96);
      amplitude = askQuestion("What amplitude do you want thet synth to play?", 0.0, 1.0);
      numVoices = askQuestion("How many voices do you want?", 1, 6);
      detunePercentage = askQuestion("How much detune do you want? (0 - 100%)", 0, 100);
  }

  //possible synth options
  Synth* synths[2]= {new FmSynth(carrierFreq, carrierAmp, waveform, modulatorFreq, modulatorAmp), new SuperSynth(note, amplitude, numVoices, detunePercentage)};

  Synth* chosenSynth = synths[synthChoice];
  
  auto callback = CustomCallback {};
  auto jackModule = JackModule { callback };

  callback.setSynth(chosenSynth); //set selected synth

  bool enableLFO = askQuestion("Would you like some LFO on your pitch?");

  if (enableLFO) {
    int waveform = askQuestion("What should be the waveform of the LFO?", {"Sine", "Square", "Saw"}, false, 15);
    float LFOfreq = askQuestion("What should be the frequency of the LFO?", 1, 20);
    float LFOdepth = askQuestion("What should be the depth of the LFO?", 0.0, 1.0);    
    callback.synth->setLFO(waveform, LFOfreq, LFOdepth);
  }

  chosenSynth->setEnv(10, 300, 0.0, 10);

  bool playMelody;

  playMelody = askQuestion("Do you want to play a melody?"); //returns true or false
  Melody* melody;

  if (playMelody) {
      melody = new Melody();
      int numNotes = askQuestion("How many notes should the melody have?", 1, 100);
      melody->addNote(numNotes, note);
      int BPM = askQuestion("What should be the BPM of the melody?", 1, 800);
    melody->play(BPM, chosenSynth); //BPM, synth
  }

  jackModule.init(0, 1);

  bool running = true;
  while (running) {
      switch (std::cin.get()) {
          case 'q':
            if (playMelody) {
              melody->stop();
              delete melody;
            }
              running = false;    
      }
  }

  AudioToFile audioFile = AudioToFile();
  audioFile.write(callback);

  //end the program
  return 0;
} // main()
