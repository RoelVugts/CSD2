import simpleaudio as sa
import random
import time
import threading


kick = sa.WaveObject.from_wave_file("audioFiles/Kick.wav")
snare = sa.WaveObject.from_wave_file("audioFiles/Snare.wav")

audioSamples = [kick, snare]

events = []

print("\nWelcome to the irregular beat generator! :)\n")

while True: #Ask user to input BPM
    try:
        BPM = int(input("Please enter BPM: "))
        print(f'BPM is set to {BPM}')
        break
    except ValueError:
        print("Error: BPM has to be an integer\n")



while True: #Ask user to input time signature
    try:
        beatsPerMeasure = int(input("\nPlease enter the beats per measure: "))
        beatValue = int(input("Please enter the note value counted as beat: "))
        print(f'\n                       {beatsPerMeasure}')
        print("time signature set to: -")
        print(f'                       {beatValue}\n')
        break
    except ValueError:
        print("Error: unvalid time signature entered")



def createTimestamps(): #function that creates timestamps
    global timestamps
    global stampsBarOne
    global durations
    global sequenceLength

    timeQuarterNote = 60 / BPM #calculate time (in seconds) per quarter note
    noteRatios = [1, 0.5, 0.25] #Quarter-, eight- and sixteenth -notes
    sequenceLength = timeQuarterNote * (beatsPerMeasure * 4) #Set sequence length to 4 bars

    timestamps = [] #create array for timestamps
    timestamps.clear() #clear array if re-running function
    timestamps.append(0.0) #first timestamp starts always at 0.0 seconds

    durations = [] 
    durations.clear()
    #print(f'Timestamp {len(timestamps)}: {timestamps[-1]}')

    while timestamps[-1] < sequenceLength/4.0: #create timestamps for x amount of time (sequenceLength)
        durations.append(timeQuarterNote * noteRatios[random.randint(0, len(noteRatios) -1)]) #choose a random note value
        if (durations[-1] + timestamps[-1]) < (sequenceLength/4): #if timestamp does not exceed sequenceLength --> add to array
            timestamps.append(durations[-1] + timestamps[-1]) #add notevalue to last timestamp to move forward in time
            stampsBarOne = len(timestamps) #amount of stamps in first bar
        else:
            durations[-1] = sequenceLength/4.0 - timestamps[-1] #make last timestamp fit bar
            break

    for j in range(2): #create 2 copies of first bar
        for i in range(stampsBarOne): #copy timestamps in first bar to second bar 
            timestamps.append(timestamps[-1] + durations[-1])
            durations.append(durations[i]) #copy durations from previous bar
   
    while timestamps[-1] < sequenceLength: #create timestamps for last bar
        if (durations[-1] + timestamps[-1]) < (sequenceLength): #if timestamp does not exceed sequenceLength --> add to array
                timestamps.append(durations[-1] + timestamps[-1]) #add notevalue to last timestamp to move forward in time
                durations.append(timeQuarterNote * noteRatios[random.randint(0, len(noteRatios) -1)]) #choose a random note value
        else:     
            durations[-1] = sequenceLength - timestamps[-1] #make last timestamp fit bar
            break
    return timestamps
    

def createInstruments():
    global instruments
    global instrumentNames
    instruments = []
    instruments.clear()
    sampleNames = ["Kick", "Snare"]
    instrumentNames = []
    instrumentNames.clear()
    for i in range(stampsBarOne): #create instruments for first bar
        randomInst = random.randint(0,len(audioSamples)-1)
        instruments.append(audioSamples[randomInst])
        instrumentNames.append(sampleNames[randomInst])
    
    for j in range(2): #copy first bar 2 times
        for i in range(stampsBarOne):
            instruments.append(instruments[i])
            instrumentNames.append(instrumentNames[i])

    stampsLastBar = len(timestamps) - stampsBarOne*3

    for i in range(stampsLastBar): #create instruments for last bar
        randomInst = random.randint(0,len(audioSamples)-1)
        instruments.append(audioSamples[randomInst])
        instrumentNames.append(sampleNames[randomInst])

events = []

def createEvents(): #add event info to dictionary in event array
    events.clear()
    for i in range(len(timestamps)):
        events.append({"Timestamp" : timestamps[i], "Sample": instruments[i], "InstrumentName": instrumentNames[i], "Duration": durations[i]})
        print(f'Timestamp {i}: {events[i]["Timestamp"]} ; {events[i]["InstrumentName"]} ; Duration: {events[i]["Duration"]}')
        if len(events) % (stampsBarOne) == 0:
            if timestamps[i] <= (sequenceLength/4) * 3:
                print("\n") #leave a blank line for every bar



createTimestamps()
createInstruments()


createEvents()



def playSequencer():
    startTime = time.time()
    index = 0
    while True:
        if index < (len(timestamps)):
            timer = time.time() - startTime
            if timer > events[index]["Timestamp"]:
                events[index]["Sample"].play()
                print(f'Timestamp {index}: {events[index]["Timestamp"]} ; {events[index]["InstrumentName"]}')
                index += 1
                time.sleep(0.001) #Reduce CPU usage
            elif (keyInput == "x") or (keyInput == "X"):
                break #break while loop if user exits sequencer
        else:
            index = 0
            startTime = time.time()

threadIndex = 0
t = []

def startThread(): #function to create a new thread when restarting sequencer
    global threadIndex
    global t
    t.append(threading.Thread(target=playSequencer))
    print(f'Length: {len(t)}')
    print(f'\nThreadIndex: {threadIndex}')
    t[threadIndex].start()

def stopThread(): #function to stop current thread
    global threadIndex
    if threading.active_count() > 1: #check if there are more threads running than 1 (main thread)
        t[-1].join() #close thread if thread is active
        threadIndex += 1 #move index up for restarting thread

storeInput = "" #create variable scoreInput for while loop

while True: #while loop with 2 while loops. 1. for asking to start or exit sequencer. 2. For store options or to create new beat, and then go back to while loop 1 --> start sequencer
    if storeInput != "X": #if user input did not exit program than stay in while loop, else break
        while True:
            keyInput = input("\nGo = start sequencer\nX = exit sequencer\n")
            if (keyInput == "Go") or (keyInput == "go"):
                startThread() #create thread to start the sequencer
            elif (keyInput == "x") or (keyInput == "X"):
                stopThread() #stop thread
                break
            else:
                print("False input")
                continue

        while True:
            storeInput = input("\nWould you like to store this beat?\nY = Yes, store this beat!\nN = No, create a new beat\nX = Exit program\n")
            if storeInput == "Y":
                dummy = 5
                #storemidi
            elif storeInput == "N":
                createTimestamps()
                createInstruments()
                createEvents()
                break
            elif storeInput =="X":
                break
            else:
                print("False input\n")
        continue
    else:
        break