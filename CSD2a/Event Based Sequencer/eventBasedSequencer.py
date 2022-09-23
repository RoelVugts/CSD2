import random
import simpleaudio as sa

class Event:
    def __init__(note, timestamp, instrument, velocity, duration):
        note.timestamp = timestamp
        note.instrument = instrument
        note.velocity = velocity
        note.duration = duration

kick = sa.WaveObject.from_wave_file("audioFiles/Kick.wav")
snare = sa.WaveObject.from_wave_file("audioFiles/Snare.wav")
chord = sa.WaveObject.from_wave_file("audioFiles/F_Chord.wav")

audioSamples = [kick, snare, chord]



while True:
    try:
        BPM = int(input("Please enter BPM: "))
        print("BPM set to " + str(BPM))
        break
    except ValueError:
        print("BPM needs to be an integer")

def createTimestamps(BPM):
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
                timestamps.append(notestamp[i]) #add timestamp to array
    
    createNotestamp() #create the Timestamps

    while len(timestamps) < 16: #make sure minimal 16 timestamps are created
        print("Amount: " + str(len(timestamps)) + " (not enough timestamps)")
        createNotestamp()
        print("Creating new timestamps..")
    else:
        #print("Timestamps: " + str(timestamps))
        return timestamps



def createInstruments(samples):
    global instruments
    instruments = []
    for i in range(len(timestamps)): #voor aantal timestamps
        instruments.append(samples[random.randint(0, len(samples) - 1)]) #choose random between souns in sample array
    #print("Instruments: " + str(instruments))
    return instruments

def createVelocities():
    global velocities
    velocities = []
    for i in range(len(timestamps)): #voor aantal timestamps
        velocities.append(random.randint(50, 127)) #create random velocities between 50 - 127
    
    #print("Velocities: " + str(velocities))
    return velocities


#print("Timestamps: " + str(createTimestamps(BPM)))
#print("Instruments" + str(createInstruments(audioSamples)))
#print("Velocities: " + str(createVelocities()))

createTimestamps(BPM)
createInstruments(audioSamples)
createVelocities()
#print("Timestamps: " + str(timestamps))

notes = list()

for i in range(len(timestamps)):
    notes.append(Event(timestamps[i], instruments[i], velocities[i], 0))
    print("No. " + str(i))
    print("Timestamp: " + str(notes[i].timestamp))
    print("Instrument: " + str(notes[i].instrument))
    print("Velocity: " + str(notes[i].velocity))
    print("\n")