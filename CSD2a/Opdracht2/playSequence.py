import time


#Functie voor afspelen polyfone sequencer
def playSequence(BPM, numPlaybackTimes, playbackStep, audioSample, sampleIndex, audioSample1): #numPlaybackTimes = aantal steps, #playbackStep = huidige step, audioSample = lijst met audio samples, sample index = welke sample uit de lijst

    tempoInterval = 60 / BPM #berekent tijdsinterval in seconden obv BPM
    playbackCounter = 0 #reset playback naar begin van sequence (eerste step)
    noteTime = tempoInterval * (4.0 / float(playbackStep[0])) #berekent tijd van nootwaarde in seconde (duratie)
    print("NoteLength: " + str(playbackStep))
    timeStarted = time.time() #reset tijd
    play_obj = audioSample[sampleIndex].play() #Speel sample1 af
    play_obj1 = audioSample1.play() #speel sample2 af
    print("playbackCounter: " +str(playbackCounter) + " noteTime: " + str(noteTime))
    playbackCounter = playbackCounter + 1 # ga 1 step vooruit

    while playbackCounter < numPlaybackTimes:
        timer = time.time() - timeStarted # tijd gaat lopen
        if timer > noteTime: 
            play_obj.stop() 
            play_obj1.stop()
            play_obj = audioSample[sampleIndex].play()
            play_obj1 = audioSample1.play()
            timeStarted = time.time() #reset timer naar 0
            print("playbackCounter: " +str(playbackCounter) + " noteTime: " + str(noteTime))
            playbackCounter += 1
            if playbackCounter < numPlaybackTimes : #stop sequencer wanneer numplaybackTimes is bereikt
                noteTime = tempoInterval * (4.0 / playbackStep[playbackCounter - 1])

