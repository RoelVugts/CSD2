#include <iostream>
#include <thread>
#include <fstream>
#include <cmath>
#include <thread>
#include <algorithm>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/value.h>
#include <string>

#include "jack_module.h"
#include "oscillator.h"
#include "melGen.h"
#include "timer.h"
#include "callback.h"
#include "audioToFile.h"
#include "UI.h"
#include "env.h"
#include "synth.h"

#define WRITE_TO_FILE 1
#define UI 0

/*
 * NOTE: jack2 needs to be installed
 * jackd invokes the JACK audio server daemon
 * https://github.com/jackaudio/jackaudio.github.com/wiki/jackd(1)
 * on mac, you can start the jack audio server daemon in the terminal:
 * jackd -d coreaudio
 */

int main(int argc,char **argv)
{
  //FmSynth properties default values
  float carrierFreq = 500;
  float carrierAmp = 1.0;
  float modulatorFreq = 250;
  float modulatorAmp = 1.0;
  int waveform = 0;

  //Supersynth properties default values
  int note = 69;
  float amplitude = 1.0;
  int numVoices = 1;
  int detunePercentage = 5;

  //LFO settings
  bool activeLFO = false;
  int LFOwaveform = 0;
  float LFOfreq = 1;
  float LFOdepth = 1.0;

  //Envelope settings
  bool activeEnv = false;
  float attack = 10;
  float decay = 500;
  float sustain = 0.8;
  float release= 20;

  //Filter settings
  bool activeFilter = false;
  int filterMode = 0; //default to lowpass
  float cutoff = 20000;

  int synthChoice = askQuestion("What synth you want to play?", {"FmSynth", "SuperSynth"}, false, 15);
  bool defaultPreset = askQuestion("Would you like to load the default preset?");


  //Read default synth preset from JSON file
  //-------------------------------------------------
  std::ifstream inputFile("presets.json");
  Json::Reader reader;
  Json::Value settings;

  reader.parse(inputFile, settings);

  if (defaultPreset && synthChoice == 0)
  {
    carrierFreq = settings["FmSynth"]["carrierFreq"].asFloat();
    carrierAmp = settings["FmSynth"]["carrierAmp"].asFloat();
    modulatorFreq = settings["FmSynth"]["modulatorFreq"].asFloat();
    modulatorAmp = settings["FmSynth"]["modulatorAmp"].asFloat();
    waveform = settings["FmSynth"]["waveform"].asInt();
  }

  if (defaultPreset && synthChoice == 1)
  {
    note = settings["SuperSynth"]["note"].asInt();
    amplitude = settings["SuperSynth"]["amplitude"].asFloat();
    numVoices = settings["SuperSynth"]["numVoices"].asInt();
    detunePercentage = settings["SuperSynth"]["detunePercentage"].asInt();
  }
  //--------------------------------------------------

  //Load default LFO and Envelope presets from JSON file
  //---------------------------------------------------
  if (defaultPreset) 
  {
    activeLFO = settings["LFO"]["active"].asBool();
    activeEnv = settings["Env"]["active"].asBool();
    activeFilter = settings["Filter"]["active"].asBool();
    
    if (activeLFO)
    {
      LFOwaveform = settings["LFO"]["waveform"].asInt();
      LFOfreq = settings["LFO"]["LFOfreq"].asFloat();
      LFOdepth = settings["LFO"]["LFOdepth"].asFloat();
    }
    if (activeEnv)
    {
      attack = settings["Env"]["attack"].asFloat();
      decay = settings["Env"]["decay"].asFloat();
      sustain = settings["Env"]["sustain"].asFloat();
      release = settings["Env"]["release"].asFloat();
    }
    if (activeFilter)
    {
      filterMode = settings["Filter"]["mode"].asInt();
      cutoff = settings["Filter"]["cutoff"].asFloat();
    }
  }
  //---------------------------------------------------------

  //if user wants to manually adjust parameters
  //----------------------------------------------------------
  if (!defaultPreset) {
    if (synthChoice == 0) { //if user selects the FmSynth
      carrierFreq = askQuestion("What should be the frequency for the carrier? (20 - 20.000 HZ)", 20, 20000);
      carrierAmp = askQuestion("What should be the amplitude of the carrier? (0.0 - 1.0)", 0.0, 1.0);
      modulatorFreq = askQuestion("What should be the ratio for the modulator? (0.01 - 10)", 0.01, 10);
      modulatorAmp = askQuestion("What should be the amplitude of the modulator? (0.0 - 1.0)", 0.0, 1.0);\
      waveform = askQuestion("What should be the waveform of the modulator?", {"Sine", "Square", "Saw"}, false, 15);
    } else if (synthChoice == 1) { //if user selects the superSynth
        note = askQuestion("What midi note do you want the synth to play? (24 - 96)", 24, 96);
        amplitude = askQuestion("What amplitude do you want the synth to play? (0.0 - 1.0)", 0.0, 1.0);
        numVoices = askQuestion("How many voices do you want? (1 - 6)", 1, 6);
        detunePercentage = askQuestion("How much detune do you want? (0 - 100%)", 0, 100);
    }
  }
  
  if (!defaultPreset) {
    activeLFO = askQuestion("Would you like some LFO on your pitch or FM depth? (y/n)");

    if (activeLFO) {
      LFOwaveform = askQuestion("What should be the waveform of the LFO?", {"Sine", "Square", "Saw"}, false, 15);
      LFOfreq = askQuestion("What should be the frequency of the LFO? (1 - 20)", 1, 20);
      LFOdepth = askQuestion("What should be the depth of the LFO? (0.0 - 1.0)", 0.0, 1.0);    
    }
    
    activeEnv = askQuestion("Would you like an envelope on the amplitude? (y/n)");
    
    if (activeEnv) {
      attack = askQuestion("What should be the attack time? (1- 10.000 ms)", 1, 10000);
      decay = askQuestion("What should be the decay time? (1 - 10.000 ms)", 1, 10000);
      sustain = askQuestion("What should be the sustain level? (0.0 - 1.0)", 0.0, 1.0);
      release = askQuestion("What should be the release time? (1- 10.000 ms)", 1, 10000);
    }

    activeFilter = askQuestion("Would you like to filter your synth? (y/n)");

    if (activeFilter) {
      filterMode = askQuestion("What should be the filter type?", {"Lowpass", "Highpass"}, false, 100);
      cutoff = askQuestion("What should be the cutoff? (0 - 24000 HZ)", 0, 24000);
    }
  }

  //---------------------------------------------------------

  //possible synth options
  Synth* synths[2]= {new FmSynth(carrierFreq, carrierAmp, waveform, modulatorFreq, modulatorAmp), new SuperSynth(note, amplitude, numVoices, detunePercentage)};
  Synth* chosenSynth = synths[synthChoice]; //create the synth
  
  if (activeLFO) 
  {
  chosenSynth->setLFO(LFOwaveform, LFOfreq, LFOdepth);
  }
  if (activeEnv) 
  {
  chosenSynth->setEnv(attack, decay, sustain, release);
  }
  if (activeFilter)
  {
    chosenSynth->setFilter(filterMode, cutoff);
  }

  //Ask user if melody needs to be played
  //---------------------------------------------------------
  bool playMelody;

  playMelody = askQuestion("Do you want to play a melody? (y/n)"); //returns true or false
  Melody* melody;

  if (playMelody) {
      melody = new Melody();
      int numNotes = askQuestion("How many notes should the melody have? (1 - 100)", 1, 100);
      melody->addNote(numNotes, note);
      int BPM = askQuestion("What should be the BPM of the melody? (1 - 800)", 1, 800);
    melody->play(BPM, chosenSynth); //BPM, synth
  }
  //---------------------------------------------------------


  //create callback
  auto callback = CustomCallback {};
  auto jackModule = JackModule { callback };

  callback.setSynth(chosenSynth); //set selected synth

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

  //Write audio to file
  AudioToFile audioFile = AudioToFile();
  audioFile.write(callback);


  //Store current settings in JSON object
  settings["FmSynth"]["carrierFreq"] = carrierFreq;
  settings["FmSynth"]["carrierAmp"] = carrierAmp;
  settings["FmSynth"]["modulatorFreq"] = modulatorFreq;
  settings["FmSynth"]["modulatorAmp"] = modulatorAmp;
  settings["FmSynth"]["waveform"] = waveform;
  
  settings["SuperSynth"]["note"] = note;
  settings["SuperSynth"]["amplitude"] = amplitude;
  settings["SuperSynth"]["numVoices"] = numVoices;
  settings["SuperSynth"]["detunePercentage"] = detunePercentage;

  settings["LFO"]["active"] = activeLFO;
  settings["LFO"]["waveform"] = LFOwaveform;
  settings["LFO"]["LFOfreq"] = LFOfreq;
  settings["LFO"]["LFOdepth"] = LFOdepth;
    
  settings["Env"]["active"] = activeEnv;
  settings["Env"]["attack"] = attack;
  settings["Env"]["decay"] = decay;
  settings["Env"]["sustain"] = sustain;
  settings["Env"]["release"] = release;

  settings["Filter"]["active"] = activeFilter;
  settings["Filter"]["mode"] = filterMode;
  settings["Filter"]["cutoff"] = cutoff;


  if (askQuestion("Save current settings as default preset?")) {
    std::ofstream outputFile("presets.json");
    outputFile << settings << std::endl;
  }

  //end the program
  return 0;
} // main()
