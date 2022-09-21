

import time
import simpleaudio as sa
import random
import threading

sample = sa.WaveObject.from_wave_file("audioFiles/Pop.wav")
sample1 = sa.WaveObject.from_wave_file("audioFiles/Dog2.wav")

BPM = 120
loopInput = "a"
isPlaying = True

print("The default BPM is set to 120")

while True:
    BPM = input("Please enter BPM or press enter for default BPM: ")
    if (BPM == ""): #if pressed enter set bpm to 120 (default)
        BPM = 120
        print("BPM set to 120 (Default)")
        break #exit while loop
    else:
        try:
            int(BPM)#check if input is an integer and if yes set BPM to input
            print("BPM set to " + str(BPM)) 
            break #exit while loop
        except ValueError: 
            continue #Else ask question again

noteDurations = [0.5, 0.25, 0.25, 0.5, 0.5, 0.5, 0.25, 0.25, 1.0]
timestamps = []
noteIntervals = []

def durationsToTimestamps16th(noteDurations):
    global timestamps  #create new list

    timestamps.clear() #clear list (in case of calling the function again)
    timestamps.append(0.0) #set first timestamp

    for n, note in enumerate(noteDurations):
        timestamps.append((note * 4) + timestamps[n]) #convert notedurations to timestamps and fill list
    return timestamps #kan deze lijst worden gemaakt zonder eerst de variabele op regel 24 te maken?

print("16ths timestamps: " + str(durationsToTimestamps16th(noteDurations)))

def timestampToInterval(timestamps, BPM):
    global noteIntervals

    noteIntervals.clear()

    for stamp in timestamps:
        noteIntervals.append((stamp / 4) * (60 / int(BPM)))
    return noteIntervals

print("NoteIntervals: " + str(timestampToInterval(timestamps, BPM)))

def startSequencer(sample, sample1):
    print("startSequencer")
    startTime = time.time()
    index = 1
    play_obj = sample.play()
    play_obj1 = sample1.play()
    while isPlaying and index < len(noteIntervals):
        timer = time.time() - startTime
        if (timer > noteIntervals[index]):
            play_obj.stop()
            play_obj1.stop()
            play_obj = sample.play()
            play_obj1 = sample1.play()
            index += 1
            time.sleep(0.001) #Reduce CPU usage
        if index == len(noteIntervals):
            index = 1
            random.shuffle(noteDurations) #shuffle the list
            durationsToTimestamps16th(noteDurations)
            timestampToInterval(timestamps, BPM)
            startTime = time.time() #reset time
            #print("NoteIntervals: " + str(noteIntervals))
    


t = threading.Thread(target=startSequencer, args=(sample, sample1)) #Assign thread
t.start() #run function in thread

while True:
    keyInput = input("Change BPM or press q to exit: ")
    if (keyInput == "q"): #if pressed enter set bpm to 120 (default)
        isPlaying = False
        t.join() #exit StartSequencer function
        break #exit while loop
    else:
        try:
            int(keyInput)#check if input is an integer and if yes set BPM to input
            BPM = keyInput
            print("BPM set to " + str(BPM)) 
        except ValueError: 
            continue #Else ask question again
