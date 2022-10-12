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
        BPM = int(input("Please enter BPM: \n> "))
        print(f'BPM is set to {BPM}')
        break
    except ValueError:
        print("Error: BPM has to be an integer\n")



while True: #Ask user to input time signature
    try:
        beatsPerMeasure = int(input("\nPlease enter the beats per measure: \n> "))
        beatValue = int(input("\nPlease enter the note value counted as beat (4-8-16): \n> "))
        print(f'\n                       {beatsPerMeasure}')
        print("time signature set to: -")
        print(f'                       {beatValue}\n')
        break
    except ValueError:
        print("Error: unvalid time signature entered")

timeQuarterNote = (60 / BPM)   #calculate time (in seconds) per qnote counted as beat
noteRatios = [1, 0.5, 0.25] #Quarter-, eight- and sixteenth -notes
sequenceLength = (timeQuarterNote / (beatValue/4)) * beatsPerMeasure #Length of bar in seconds
sixteenthAmount = int(beatsPerMeasure / (beatValue/16))



rhythms = []
#Properties of rhythm
rhythms.append({"syncopation": 0.5, "beatRepetition": 1.0, "Density": 0.4, "firstBeat": 0.1})
print(f'Syncopation: {rhythms[0]["syncopation"]} ; beatRepetition: {rhythms[0]["beatRepetition"]} ; Density: {rhythms[0]["Density"]} ; firstBeat: {rhythms[0]["firstBeat"]} ')

#Syncope = Kans dat er geen sample op de tel wordt gespeeld
#repetition = hoe veel kans er is dat beat zich herhaalt
#density = hoe veel noten er in een beat zitten
#firstBeat = Kans dat iets op de eerste tel valt

def createRhythm():
    global sixteenths
    global timestamps
    global durations
    global stampsOneBeat

    timestamps = []
    timestamps.clear() #clear array if re-running function

    durations = [] 
    durations.clear()

    sixteenths = []
    sixteenths.clear()

    barIndex = 0 #keeps count of how many bars we have created

    print(f'SixteenthAmount: {sixteenthAmount}')
    print(f'beatsPerMeasure {beatsPerMeasure}')
    
    def createOneBeat():
        for i in range(0, int((sixteenthAmount/beatsPerMeasure))):
            if i+(barIndex*4) == 0:
                if random.random() < rhythms[0]["firstBeat"]: #Chance a stamp is on first beat
                    sixteenths.append(1 + (barIndex * 4)) #add to first beat of bar
            elif i % (16/beatValue) == 0 or i != 0: #for every beat thats not the first beat
                if random.random() > rhythms[0]["syncopation"]: #if syncopation is low (0.0)
                    sixteenths.append(i+1 + (barIndex * 4)) #Add stamp on beat/pulse, else don't
            elif i % (16/beatValue) != 0: #for every other position
                if random.random() < rhythms[0]["Density"]: #create stamp if < % density
                    sixteenths.append(i+1 + (barIndex*4)) 
    
    
    
    createOneBeat()
    stampsOneBeat = len(sixteenths) #var to store amount of stamps in first beat

    for i in range(1, 4): #(1, 2, 3) create 3 more beats
        if random.random() < rhythms[0]["beatRepetition"]:
            for j in range(stampsOneBeat):
                sixteenths.append((i*4) + sixteenths[j]) #repeat first beat to next beat
        else:
            barIndex += 1
            createOneBeat() #create a new beat


    for sixteenth in sixteenths:
        timestamps.append((sixteenth/sixteenthAmount) * sequenceLength)

    for i in range(len(timestamps)):
        if i+1 < len(timestamps):
            durations.append(timestamps[i+1] - timestamps[i])
        else:
            durations.append(sequenceLength - timestamps[i])

    print(f'sixteenth: {sixteenths}')
    print(f'timestamps: {timestamps}')


createRhythm()

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


    for i in range(stampsOneBeat): #create instruments for first bar
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
    
  #  stampsLastBar = len(timestamps) - stampsBarOne*3 #calculate amount of stamps in last bar (fill)

    # for i in range(stampsLastBar): #create instruments for last bar
    #     randomInst = random.randint(1,len(audioSamples)-1)
    #     instruments.append(audioSamples[randomInst])
    #     if randomInst != 2:
    #         if random.randint(0,100) < 25:
    #             instruments2.append(hiHat)
    #         else:
    #             instruments2.append("Empty")
    #     else:
    #         instruments2.append("Empty")        
    #     instrumentNames.append(sampleNames[randomInst])

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
        
        # if len(events) % (stampsBarOne) == 0: #for every bar
        #     if timestamps[i] <= (sequenceLength/4) * 3:
        #         print("\n") #leave a blank line for every bar


def createNewBeat(): #function that generates a new 4 bar rhythm
    #createTimestamps()
    #timestampsToSixteenths()
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
    for event in events: #convert samples to midi pitch
        if event["InstrumentName"] == "Kick":
            pitch = 60
        elif event["InstrumentName"] == "Snare":
            pitch = 61
        elif event["InstrumentName"] == "HiHat":
            pitch = 62
        
        time = (event["Sixteenth"] -1) / 4 #timestamp in beats 
        duration = event["Duration"] / (60 / BPM) #duration in beats
        volume = event["Velocity"]

        newMidiFile.addNote(track, channel, pitch, time, duration, volume)

    outputFilePath = input("\nEnter file name and/or directory: \n> ") + str(".mid") #create filename
    
    with open(outputFilePath, "wb") as output_file: #open and write to file
        newMidiFile.writeFile(output_file)
    
    return print(f'MIDI File created in {outputFilePath}')

storeInput = "" #create variable scoreInput for while loop

while True: #while loop with 2 while loops. 1. for asking to start or exit sequencer. 2. For store options or to create new beat, and then go back to while loop 1 --> start sequencer
    if storeInput != "X" and storeInput != "Y": #if user input did not exit program than stay in while loop, else break
        while True:
            keyInput = input("\nGo = start sequencer\nX = exit sequencer\nN = Create New Beat\n> ")
            if (keyInput == "Go"): 
                stopThread()  
                startThread() #create thread to start the sequencer
            elif (keyInput == "X"):
                stopThread() #stop thread
                break
            elif (keyInput == "N"):
                #createNewBeat()
                createRhythm()
            else:
                print("False input")
                continue

        while True:
            storeInput = input("\nWould you like to store this beat?\nY = Yes, store this beat!\nN = No, create a new beat\nX = Exit program\n> ")
            if storeInput == "Y":
                storeToMidi()
                break
            elif storeInput == "N":
                #createNewBeat()
                createRhythm()
                break
            elif storeInput == "X":
                break
            else:
                print("False input\n")
    else:
        break
