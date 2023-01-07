#pragma once

class Filter {
    public:
        float lowpass(float inputValue);
        float highpass(float inputValue);
        void setCutoff(float cutoff);


    private:
        float cutoff;
        float output = 0.0;
        float output2 = 0.0;
};