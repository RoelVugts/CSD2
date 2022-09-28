import random
import simpleaudio as sa
import time
import threading

class Event: #Class for storing event information
    def __init__(note, timestamp, instrument, instrumentName, velocity, duration):
        note.timestamp = timestamp
        note.instrument = instrument #wav file
        note.instrumentName = instrumentName #reference name
        note.velocity = velocity
        note.duration = duration

notes = [] #array to store class instances

kick = sa.WaveObject.from_wave_file("audioFiles/Kick.wav")
snare = sa.WaveObject.from_wave_file("audioFiles/Snare.wav")
chord = sa.WaveObject.from_wave_file("audioFiles/F_Chord.wav")

audioSamples = [kick, snare, chord] #store samples in array

while True: #Ask user for BPM
    try:
        BPM = int(input("Please enter BPM: "))
        print("BPM set to " + str(BPM))
        break
    except ValueError:
        print("BPM needs to be an integer")

def createTimestamps(BPM): #function that creates timestamps (random)
    noteDurations = [1, 0.5, 0.25] #quarter, eight and sixteenth notes
    tempo = 60 / BPM #calculate time per beat (in seconds)
    playTime = tempo * 16 #calculate time of 4 bars (16 beats)

    def createNotestamp():
        global timestamps #global var since we will return this
        notestamp = [] #list that gets pushed into timestamps[]
        timestamps = [] #timestamps list
        notestamp.clear() #reset list when re-running function
        timestamps.clear() #reset list when re-running function
        notestamp = [0.0] #always start at 0.0 s
        timestamps = [0.0] #always start at 0.0 s
        i = 0 #iterator for while loop

        while notestamp[len(notestamp) -1] < playTime: #w;hile last notestamp does not exceed max amount of time
            i += 1 #move index
            notestamp.append(tempo * noteDurations[random.randint(0, len(noteDurations) -1)] + notestamp[i-1]) #calculate timestamp
            if notestamp[i] < playTime : #if timestamp does not exceed 2 bars
                timestamps.append(round(notestamp[i], 5)) #add timestamp to array
    
    createNotestamp() #create the Timestamps

    while len(timestamps) < 16: #make sure minimal 16 timestamps are created
        print("Amount: " + str(len(timestamps)) + " (not enough timestamps)")
        createNotestamp()
        print("Creating new timestamps..")
    else:
        #print("Timestamps: " + str(timestamps))
        return timestamps

def createInstruments(samples): #function that adds samples to the timestamps
    global instruments
    global instrumentNames
    instruments = [] #array for the wave objects
    instrumentNames = [] #array for the string variabels (as reference)
    pseudoRandom = 0
    for i in range(len(timestamps)): #voor aantal timestamps
        if timestamps[i] * BPM % 240 == 0:
            pseudoRandom = samples[0] #Kick on every first beat
        else:
            pseudoRandom = samples[random.randint(0, len(samples) - 1)]
        instruments.append(pseudoRandom) #choose random between sounds in sample array
        
        if pseudoRandom == kick:
            instrumentNames.append("Kick")
        elif pseudoRandom == snare:
            instrumentNames.append("Snare")
        elif pseudoRandom == chord:
            instrumentNames.append("Chord")

def createVelocities(): #function that adds velocities to the timestamps
    global velocities
    velocities = []
    for i in range(len(timestamps)): #voor aantal timestamps
        velocities.append(random.randint(50, 127)) #create random velocities between 50 - 127
    
    #print("Velocities: " + str(velocities))
    return velocities

createTimestamps(BPM)
createInstruments(audioSamples)
createVelocities()

for i in range(len(timestamps)): #push arrays into class objects
    notes.append(Event(timestamps[i], instruments[i], instrumentNames[i], velocities[i], 0)) #create objects
    print(f'No. {i} ; Timestamp: {notes[i].timestamp} ; Instrument: {notes[i].instrumentName} ; Velocity: {notes[i].velocity}')
    

print(f'Created {len(timestamps)} Events')

def playSequencer(eventArray): #Functie die de sequence speelt (Event Handler)
    startTime = time.time() #set start time
    index = 0

    while index < len(eventArray):
        timer = time.time() - startTime #start timer
        if timer > eventArray[index].timestamp: 
                eventArray[index].instrument.play()
                print(f'Timestamp: {eventArray[index].timestamp} ; Velocity: {eventArray[index].velocity} ; Instrument: {eventArray[index].instrumentName}')
                index += 1


while True:
    keyInput = input("\nStart the sequencer? [Y/n]")
    if (keyInput == "Y"):
        playSequencer(notes)
    elif (keyInput == "n"):
        break
    else:
        continue
    