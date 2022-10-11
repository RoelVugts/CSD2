import simpleaudio as sa
import random
import time
import threading
from midiutil import MIDIFile


kick = sa.WaveObject.from_wave_file("audioFiles/Kick.wav")
snare = sa.WaveObject.from_wave_file("audioFiles/Snare.wav")
hiHat = sa.WaveObject.from_wave_file("audioFiles/HiHat.wav")

audioSamples = [kick, snare, hiHat]

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


    timeQuarterNote = (60 / BPM)   #calculate time (in seconds) per qnote counted as beat
    noteRatios = [1, 0.5, 0.25] #Quarter-, eight- and sixteenth -notes
    sequenceLength = (timeQuarterNote / (beatValue/4)) * (beatsPerMeasure * 4) #Set sequence length to 4 bars

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
   
    while timestamps[-1] < sequenceLength: #create random timestamps for last bar
        if (durations[-1] + timestamps[-1]) < (sequenceLength): #if timestamp does not exceed sequenceLength --> add to array
                timestamps.append(durations[-1] + timestamps[-1]) #add notevalue to last timestamp to move forward in time
                durations.append(timeQuarterNote * noteRatios[random.randint(0, len(noteRatios) -1)]) #choose a random note value
        else:     
            durations[-1] = sequenceLength - timestamps[-1] #make last timestamp fit bar
            break
    
    for i in range(0,len(timestamps)):
        timestamps[i] = round(timestamps[i], 3) #round off floating point error
    
    for i in range(0, len(durations)):
        durations[i] = round(durations[i], 3) #round off floating point error

def timestampsToSixteenths():
    global sixteenths
    sixteenths = []
    sixteenths.clear()
    for stamp in timestamps:
        sixteenths.append(round((stamp / ((60/BPM)*0.25)) + 1)) #convert timestamp to stixteenth


def createInstruments():
    global instruments
    global instrumentNames
    global instruments2
    instruments = []
    instruments.clear()
    instruments2 = []
    instruments2.clear()
    sampleNames = ["Kick", "Snare", "HiHat"]
    instrumentNames = []
    instrumentNames.clear()


    for i in range(stampsBarOne): #create instruments for first bar
        if sixteenths[i] % 16 == 1:         #Every first beat is probably kick
            if random.randint(0, 100) < 80:
                randomInst = 0 # 0 = Kick
            elif 80 <= random.randint(0, 100) <= 90:
                randomInst = 1 # 1 = Snare
            else:
                randomInst = 2 # 2 = HiHat
        elif sixteenths[i] % 8 == 5:        #Every 2nd and 4th beat is probaly snare
            if random.randint(0, 100) < 90:
                randomInst = 1
            elif 90 <= random.randint(0, 100) <= 95:
                randomInst = 0
            else:
                randomInst = 2
        else:
            if random.randint(0, 100) < 50: # Everything else is most probable HiHat
                randomInst = 2 
            elif 50 <= random.randint(0, 100) <= 70:
                randomInst = 0 
            else:
                randomInst = 1
            
        #code to generate 2nd sample (hihat) that will be played simultaneous
        #i chose only for a hihat since i don't want a kick and snare to be played at the same time
        if randomInst != 2:  #if the first sample is not a hiHat
            if random.randint(0,100) < 50:
                instruments2.append(hiHat) #50% chance that a hiHat sample is added to kick or snare
            else:
                instruments2.append("Empty") #50% that no extra instrument is added
        else:
            instruments2.append("Empty") #if the first sample is a hiHat dont add a 2nd hihat

        instruments.append(audioSamples[randomInst])
        instrumentNames.append(sampleNames[randomInst])
    
    for j in range(2): #copy first bar 2 times
        for i in range(stampsBarOne):
            instruments.append(instruments[i])
            instruments2.append(instruments2[i])
            instrumentNames.append(instrumentNames[i])

    stampsLastBar = len(timestamps) - stampsBarOne*3 #calculate amount of stamps in last bar (fill)

    for i in range(stampsLastBar): #create instruments for last bar
        randomInst = random.randint(1,len(audioSamples)-1)
        instruments.append(audioSamples[randomInst])
        if randomInst != 2:
            if random.randint(0,100) < 25:
                instruments2.append(hiHat)
            else:
                instruments2.append("Empty")
        else:
            instruments2.append("Empty")        
        instrumentNames.append(sampleNames[randomInst])

def createVelocities():
    global velocities
    velocities = []
    velocities.clear()

    for i in range(len(sixteenths)): #create instruments for first bar
        if (sixteenths[i]) % 4 == 1:
            randomVel = random.randint(100, 127)
            velocities.append(randomVel)
        else:
            randomVel = random.randint(40, 70)
            velocities.append(randomVel)

events = []

def createEvents(): #add event info to dictionary in event array
    events.clear()
    for i in range(len(timestamps)): #for loop to push individual arrays in dictionary
        events.append({"Timestamp" : timestamps[i], "Sixteenth": sixteenths[i], "Sample": instruments[i], "Sample2": instruments2[i], "InstrumentName": instrumentNames[i], "Duration": durations[i], "Velocity": velocities[i]})
        print(f'Timestamp {i}: {events[i]["Timestamp"]:<8} ; Sixteenth: {events[i]["Sixteenth"]} ;  {events[i]["InstrumentName"]} ; Duration: {events[i]["Duration"]} ; Velocity: {velocities[i]}')
        
        if len(events) % (stampsBarOne) == 0: #for every bar
            if timestamps[i] <= (sequenceLength/4) * 3:
                print("\n") #leave a blank line for every bar




def createNewBeat(): #function that generates a new 4 bar rhytm
    createTimestamps()
    timestampsToSixteenths()
    createInstruments()
    createVelocities()
    createEvents()

createNewBeat()

def playSequencer():
    startTime = time.time()
    index = 0
    while True:
        timer = time.time() - startTime
        if index < (len(timestamps)):
            
            if timer > events[index]["Timestamp"]: #trigger sample if timestamp = timer
                events[index]["Sample"].play()
                if events[index]["Sample2"] != "Empty": #Play sample2 simultaneous if not empty
                    events[index]["Sample2"].play()
                print(f'Timestamp {index}: {events[index]["Timestamp"]} ; {events[index]["InstrumentName"]}')
                if (index+1) % (stampsBarOne) == 0:
                    if timestamps[index] <= (sequenceLength/4) * 3:
                        print("\nbar end") #leave a blank line for every bar
                index += 1               
            elif (keyInput == "x") or (keyInput == "X"):
                break #break while loop if user exits sequencer
        else:
            if timer > sequenceLength:
                index = 0
                startTime = time.time()
                print("\nloop end")
        time.sleep(0.001) #Reduce CPU usage

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


def storeToMidi():
    newMidiFile = MIDIFile(1) #midifile with 1 track
    track = 0
    channel = 0
    time = 0.0

    newMidiFile.addTempo(track, time, BPM)
    for event in events:
        if event["InstrumentName"] == "Kick":
            pitch = 60
        elif event["InstrumentName"] == "Snare":
            pitch = 61
        elif event["InstrumentName"] == "HiHat":
            pitch = 62
        
        time = (event["Sixteenth"] -1) / 4 #timestamp in beats
        duration = event["Duration"] / (60 / BPM) #duration in time
        volume = event["Velocity"]


        #print(track, channel, pitch, time, duration, volume)
        #MIDIFile.addNote(track, channel, pitch, time, duration, volume)
        newMidiFile.addNote(track, channel, pitch, time, duration, volume)

    outputFilePath = input("Enter file name and/or directory: ") + str(".mid")
    
    with open(outputFilePath, "wb") as output_file:
        newMidiFile.writeFile(output_file)
    
    return print(f'MIDI File created in {outputFilePath}')

storeInput = "" #create variable scoreInput for while loop

while True: #while loop with 2 while loops. 1. for asking to start or exit sequencer. 2. For store options or to create new beat, and then go back to while loop 1 --> start sequencer
    if storeInput != "X" and storeInput != "Y": #if user input did not exit program than stay in while loop, else break
        while True:
            keyInput = input("\nGo = start sequencer\nX = exit sequencer\nN = Create New Beat\n\n")
            if (keyInput == "Go"): 
                stopThread()  
                startThread() #create thread to start the sequencer
            elif (keyInput == "X"):
                stopThread() #stop thread
                break
            elif (keyInput == "N"):
                createNewBeat()
            else:
                print("False input")
                continue

        while True:
            storeInput = input("\nWould you like to store this beat?\nY = Yes, store this beat!\nN = No, create a new beat\nX = Exit program\n")
            if storeInput == "Y":
                storeToMidi()
                break
            elif storeInput == "N":
                createNewBeat()
                break
            elif storeInput == "X":
                break
            else:
                print("False input\n")
    else:
        break
