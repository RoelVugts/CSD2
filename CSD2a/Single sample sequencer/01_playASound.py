"""
An example project in which three wav files are used.

------ EXERCISES ------

- What does the function wait_done() do?

- Answer the following question before running the code:
  Do you expect to hear the samples played simultaneously or one after the other?
  Why?

- Alter the code:
  Play the sounds one after the other and then simultaneously.

- Alter the code:
  Ask the user to choice which one of the three samples should be played and
  only play the chosen sample.

- Give yourself a couple of assignments, like playing one of the samples ten
  times before the others are played, playing all samples a given number
  of times or playing the samples one after the other with 1 second between
  them.

"""

# simpleaudio is imported as sa -> shorter name
import simpleaudio as sa
import time

# load audio files
sampleHigh = sa.WaveObject.from_wave_file("audioFiles/Pop.wav")
sampleMid = sa.WaveObject.from_wave_file("audioFiles/Laser1.wav")
sampleLow = sa.WaveObject.from_wave_file("audioFiles/Dog2.wav")

userSample = int(input("Enter sample (1 - 3) you would like to hear: "))

audioSamples = [sa.WaveObject.from_wave_file("audioFiles/Pop.wav"), sa.WaveObject.from_wave_file("audioFiles/Laser1.wav"), sa.WaveObject.from_wave_file("audioFiles/Dog2.wav")]

for i in range(0, 4): #speelt gekozen sample 5 keer af
  playSample = audioSamples[userSample - 1].play()
  playSample.wait_done()

#speelt samples achter elkaar af
playSample = audioSamples[0].play()
playSample.wait_done()
time.sleep(1)

playSample = audioSamples[1].play()
playSample.wait_done()
time.sleep(1)

playSample = audioSamples[2].play()
playSample.wait_done()
time.sleep(1)

"""
# play high sample
sampleHighPlay = sampleHigh.play()
# wait till sample is done playing
sampleHighPlay.wait_done()

# play mid sample
sampleMidPlay = sampleMid.play()
# wait till sample is done playing
sampleMidPlay.wait_done()

# play low sample
sampleLowPlay = sampleLow.play()
# wait till sample is done playing
sampleLowPlay.wait_done()



#play sounds simultaneously
sampleHighPlay = sampleHigh.play()
sampleMidPlay = sampleMid.play()
sampleLowPlay = sampleLow.play()
sampleHighPlay.wait_done()
sampleMidPlay.wait_done()
sampleLowPlay.wait_done()

"""