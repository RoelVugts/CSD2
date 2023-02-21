#include <sndfile.h>
#include <iostream>
#include <vector>

#pragma once

class FilePlayer {
    public:

        void open(const char* path)
        {
            SNDFILE* file = sf_open("Ready.wav", SFM_READ, &file_info);
            if(!file)
            {
                std::cout << "Unable to open audio file" << std::endl;
                return;
            }
            samples.resize(file_info.frames * file_info.channels);
            
            sf_readf_float(file, samples.data(), file_info.frames);
            std::cout << "Audio succesfully stored in buffer" << std::endl;
            sf_close(file);
        }

        float read()
        {
            if (readPos > samples.size())
            {
                readPos -= samples.size();
            }

            return samples[readPos++];
        }

        int readPos { 0 };
        SF_INFO file_info;
        std::vector<float> samples;
};