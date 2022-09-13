

import simpleaudio as sa
import random

import playSequence as playSeq #eigen module

numPlaybackTimes = 8    #amount of playbacks
timer = 0               #timer voor sequencer
playbackCounter = 0     #counter die aantal x afgespeeld bijhoudt


wave_object = [sa.WaveObject.from_wave_file("audioFiles/TestKick.wav"), sa.WaveObject.from_wave_file("audioFiles/Heavy.wav"), sa.WaveObject.from_wave_file("audioFiles/Pitched.wav"), sa.WaveObject.from_wave_file("audioFiles/Rammel.wav")]
playbackStep = [] #lijst voor de sequencer
noteDuration = [16, 8, 4, 2, 1] #lijst met nootwaarden

wave_object1 = sa.WaveObject.from_wave_file("audioFiles/Horse.wav") #sample2


for i in range(numPlaybackTimes): #voor numPlaybacktimes aantal keer
    playbackStep.append(noteDuration[random.randrange(0, 5)]) #kies random nootwaarden

kickSample = int(input("Enter the kick you want to hear (1 - 4): \n")) -1 #user input voor kick sample
BPM = int(input("Please enter BPM: \n")) #user input voor tempo

tempoInterval = 60 / BPM #berekent tijdsinterval in seconden obv BPM
print("tempoInterval: " + str(tempoInterval))


playSeq.playSequence(BPM, numPlaybackTimes, playbackStep, wave_object, kickSample, wave_object1)  #polyfone sequence player


while True:
    repeatSequence = input("Repeat? [Y/n]")
    if repeatSequence == "Y":
        playSeq.playSequence(BPM, numPlaybackTimes, playbackStep, wave_object, kickSample, wave_object1)
        continue #herhaal functie en vraag dan opnieuw
    elif repeatSequence == "n":
        print("Done, goodbye...")
        break #sluit programma
    else:
        continue #Gaat terug naar begin van while loop