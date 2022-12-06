class Synth {
    public:
        Synth();
        Synth(float frequency, float amplitude, float samplerate);
        Synth(float frequency, float amplitude);
        ~Synth();

        //getters and setters
        float getSampleRate();
        void setFrequency(float frequency);
        float getFrequency();
        void setSamplerate(float samplerate);


    protected:
        float frequency;
        float amplitude;
        float samplerate;
};