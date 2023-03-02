#include <sndfile.h>
#include <iostream>
#include <vector>
#include <array>

#pragma once


//MONO file player
class FilePlayer {
    public:

        void open(const char* path)
        {
            SNDFILE* file = sf_open("Ready.wav", SFM_READ, &file_info);
            if(!file)
            {
                std::cout << "Unable to open audio file" << std::endl;
                return;
            } else 
            {
                std::cout << "byteRate: " << sf_current_byterate(file) << std::endl;
            }

            for (int channel = 0; channel < 2; channel++)
            {
                samples[channel].resize(file_info.frames * file_info.channels);
                sf_readf_float(file, samples[channel].data(), file_info.frames);
            }
            std::cout << "Audio succesfully stored in buffer" << std::endl;
            sf_close(file);
        }

        float read(int channel)
        {
            if (readPos > samples[channel].size())
            {
                readPos -= samples[channel].size();
            }

            return samples[channel][readPos++];
        }

        long unsigned int readPos { 0 };
        SF_INFO file_info;
        std::array<std::vector<float>, 2> samples;
};