

import simpleaudio as sa
import random
import time



numPlaybackTimes = 8    #amount of playbacks
timer = 0               #timer voor sequencer
playbackCounter = 0     #counter die aantal x afgespeeld bijhoudt

#Array met kick samples
wave_object = [sa.WaveObject.from_wave_file("audioFiles/TestKick.wav"), sa.WaveObject.from_wave_file("audioFiles/Heavy.wav"), sa.WaveObject.from_wave_file("audioFiles/Pitched.wav"), sa.WaveObject.from_wave_file("audioFiles/Rammel.wav")]
playbackStep = [] #lijst voor de sequencer
noteDuration = [16, 8, 4, 2, 1] #lijst met nootwaarden


for i in range(numPlaybackTimes): #voor numPlaybacktimes aantal keer
    playbackStep.append(noteDuration[random.randrange(0, 5)]) #kies random nootwaarden

kickSample = int(input("Enter the kick you want to hear (1 - 4): \n")) -1 #user input voor kick sample
BPM = int(input("Please enter BPM: \n")) #user input voor tempo

tempoInterval = 60 / BPM #berekent tijdsinterval in seconden obv BPM
print("tempoInterval: " + str(tempoInterval))


def playSequence(): #functie voor afspelen sequencer
    global playbackCounter #waarom moet dit global zijn? is toch al global?
    global noteTime
    playbackCounter = 0 #reset playback naar begin van sequence
    noteTime = tempoInterval * (4.0 / float(playbackStep[0])) #berekent tijd van nootwaarde in seconde
    print("NoteLength: " + str(playbackStep))
    timeStarted = time.time() #reset tijd
    play_obj = wave_object[kickSample].play()
    print("playbackCounter: " +str(playbackCounter) + " noteTime: " + str(noteTime))
    playbackCounter = playbackCounter + 1

    while playbackCounter < numPlaybackTimes:
        timer = time.time() - timeStarted # tijd gaat lopen
        if timer > noteTime: 
            play_obj.stop()
            play_obj = wave_object[kickSample].play()
            timeStarted = time.time()
            print("playbackCounter: " +str(playbackCounter) + " noteTime: " + str(noteTime))
            playbackCounter += 1
            if playbackCounter < numPlaybackTimes :
                noteTime = tempoInterval * (4.0 / playbackStep[playbackCounter - 1])

playSequence()        

while True:
    repeatSequence = input("Repeat? [Y/n]")
    if repeatSequence == "Y":
        playSequence()
        continue #herhaal functie en vraag dan opnieuw
    elif repeatSequence == "n":
        print("Done, goodbye...")
        break #sluit programma
    else:
        continue #Gaat terug naar begin van while loop

