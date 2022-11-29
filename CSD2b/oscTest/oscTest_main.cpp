#include "oscTest.h"
#include <fstream>
#include <iostream>
#include <cmath>
#include <bits/stdc++.h>

using namespace std;


const int sampleRate = 44100;

int main() 
{
    remove("waveform");

    ofstream audioFile;
    audioFile.open("waveform", ios::binary);
    SineOscillator sineOsc(1000, 1.0);

    audioFile << sin(M_PI*2) << endl;
    audioFile << sin(3.1415926*2) << endl;
    audioFile << sin(3.14*2) << endl;

    for(int i = 0; i < sampleRate; i++){
        audioFile << "Sample: " << sineOsc.getSampleValue() << endl;
        sineOsc.play();
    }

    audioFile.close();

    cout << sin(M_PI*2) << endl;
    cout << sin(3.1415926*2) << endl;
    cout << sin(3.14*2) << endl;

    cout << 2*M_PI << endl;
    cout << 3.14*2 << endl;



    return 0; 
}