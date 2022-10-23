import simpleaudio as sa
import random
import time
import threading
from midiutil import MIDIFile
import askQuestion


kick = sa.WaveObject.from_wave_file("audioFiles/Kick.wav")
snare = sa.WaveObject.from_wave_file("audioFiles/Snare.wav")
hiHat = sa.WaveObject.from_wave_file("audioFiles/HiHat.wav")

audioSamples = [kick, snare, hiHat]
instrumentStrings = ["Kick", "Snare", "HiHat"]

print("\nWelcome to the irregular beat generator! :)\n")

BPM = askQuestion.askQuestion('int', "Please enter BPM", {'allowEmpty': False, 'Min': 0})
beatsPerMeasure = askQuestion.askQuestion('int', "\nPlease enter beats per measure", {'allowEmpty': False, 'Min': 0})
beatValue = askQuestion.askQuestion('int', "\nPlease enter the note value counted as beat", {'allowEmpty': False})

#Global variables
#----------------------------------------
timeQuarterNote = (60 / BPM)   #calculate time (in seconds) per qnote counted as beat
noteRatios = [1, 0.5, 0.25] #Quarter-, eight- and sixteenth -notes
sequenceLength = (timeQuarterNote / (beatValue/4)) * beatsPerMeasure*4 #Length of 4 bars in seconds
sixteenthAmount = int(beatsPerMeasure / (beatValue/16)) #total amount of sixteenths in 1 bar

rhythmProperties = [] #list to store properties of each rhythm
rhythms = [] #list to store 5 rhythms that will be generated

#Properties of rhythm
#-------------------------
#Syncope = Kans dat er geen sample op de tel wordt gespeeld
#repetition = hoe veel kans er is dat beat zich herhaalt (zowel ritme als instrumenten)
#density = hoe veel noten er in een beat zitten
#firstBeat = Kans dat iets op de eerste tel valt
#randomFill = Kans dat de laatste maat een fill is met veel random kansberekening

#function that creates 4 bar rhythm based on properties
def createRhythm(syncopation, beatRepetition, density, firstBeat, randomFill):
    #lists that will contain outputs
    rhythmProperties.append({"syncopation": round(syncopation,4), "beatRepetition": round(beatRepetition,4), "density": round(density,4), "firstBeat": round(firstBeat,4), "randomFill": round(randomFill,4)})
    timestamps = []
    durations = [] 
    sixteenths = []
    instruments = []
    instrumentNames = []
    velocities = []

    barIndex = 0 #keeps count of how many bars we have created
    
    def createOneBar():
        randomPosNeg =[1, -1] #list for deciding if syncopated offset is before or after the beat/pulse

        for i in range(0, int((sixteenthAmount))):
            if (i+(barIndex*sixteenthAmount)) % sixteenthAmount == 0:
                if random.random() < firstBeat: #Chance a stamp is on first beat
                    sixteenths.append(1 + (barIndex * sixteenthAmount)) #add to first beat of bar
                    instruments.append(kick)
                    instrumentNames.append(("Kick"))
            elif i % (sixteenthAmount/beatsPerMeasure) == 0 and i != 0: #for every beat thats not the first beat
                randomSyncope = random.random()
                if randomSyncope < syncopation and randomSyncope < density: #if syncopation is high (1.0) create a syncopation  
                    syncopatedStamp = random.randint(1,2) # add stamp with offset 1 or 2 sixteenths
                    if not sixteenths: #if list is empty
                        lastIndex = 0 #amount of indexes in list = 0
                    else:
                        lastIndex = sixteenths[-1] #if not empty set to last index in list
                    if (syncopatedStamp + lastIndex) <= (((barIndex+1)*sixteenthAmount)): # and syncopatedStamp + sixteenths[-1] in sixteenths:
                        sixteenths.append(i+1+(syncopatedStamp*random.choice(randomPosNeg)) + (barIndex * sixteenthAmount)) #Add stamp with positive or negative offset (syncopation)
                        randomSample = random.randint(0,1) #choose between kick or snare
                        instruments.append(audioSamples[randomSample])
                        instrumentNames.append(instrumentStrings[randomSample])
                else: #if syncopation is low
                    sixteenths.append(i+1 + barIndex*sixteenthAmount) #add stamp on beat
                    # print(f'On Beat: {i+1 + barIndex*sixteenthAmount}')
                    randomSample = random.randint(0,1)
                    instruments.append(audioSamples[randomSample])
                    instrumentNames.append(instrumentStrings[randomSample])
            elif i % (sixteenthAmount/beatsPerMeasure) != 0 or (i+(barIndex*sixteenthAmount)) % sixteenthAmount == 0: #for every other position
                if random.random() < density: #create stamp in between beats if density is high
                    sixteenths.append(i+1 + (barIndex*sixteenthAmount))
                    randomSample = random.randint(0, 2)
                    instruments.append(audioSamples[randomSample])
                    instrumentNames.append(instrumentStrings[randomSample])
        
    def createRandomFill():
        for i in range((sixteenthAmount*3)+1, sixteenthAmount*4): #sixteenths in last bar
            if random.random() < random.random(): #if statement for adding or not adding a stamp
                sixteenths.append(i)
                randomFillSample = random.randint(0,2)
                instruments.append(audioSamples[randomFillSample])
                instrumentNames.append(instrumentStrings[randomFillSample])


    createOneBar() #create the first bar
    sixteenths = list(dict.fromkeys(sixteenths)) #remove duplicates
    
    sixteenths.sort()
    stampsOneBar = len(sixteenths) #var to store amount of stamps in first bar

    for i in range(1, 4): #(1, 2, 3) create 3 more bars
        if i != 3 or random.random() > randomFill: #if true do not create fill
            if random.random() < beatRepetition: #if true then repeat first bar
                for j in range(stampsOneBar):
                    sixteenths.append((i*sixteenthAmount) + sixteenths[j]) #repeat first beat to next beat
                    instruments.append(instruments[j]) #repeat instruments for beat
                    instrumentNames.append(instrumentNames[j]) #repeat instruments for beat
                barIndex += 1
            else: 
                barIndex += 1
                createOneBar() #create a new psuedorandom bar
                sixteenths = list(dict.fromkeys(sixteenths)) #remove duplicates
        else:
            barIndex += 1
            createRandomFill() #create a random fill
            sixteenths = list(dict.fromkeys(sixteenths)) #remove duplicates                

    sixteenths.sort() #syncopation could create sixteenths that are lower than previous sixteenth, so list needs to be sorted

    #Create durations
    for sixteenth in sixteenths: #convert sixteenths to timestamps
        timestamps.append(round((((sixteenth-1)/(sixteenthAmount*4)) * sequenceLength),4))
        
    for i in range(len(timestamps)): #create durations (for midi output file)
        if i+1 < len(timestamps):
            durations.append(timestamps[i+1] - timestamps[i])
        else:
            durations.append(sequenceLength - timestamps[i])
    
    #create velocities
    for i in range(len(sixteenths)): #if velocity is on beat it's probably higher
        if (sixteenths[i]) % beatValue == 1:
            randomVel = random.randint(100, 127)
            velocities.append(randomVel)
        else:
            randomVel = random.randint(40, 70)
            velocities.append(randomVel)
    
    return timestamps, sixteenths, instruments, instrumentNames, durations, velocities

#function that creates events in a dictionar of a rhythm
def createEvents(timestamps, sixteenths, instruments, instrumentNames, durations, velocities): #list is a parameter since we will make a separate list per rhythm
    eventList = []

    for i in range(len(timestamps)): #for loop to push individual arrays in dictionary
        eventList.append({"Timestamp" : timestamps[i]
        , "Sixteenth": sixteenths[i]
        , "Sample": instruments[i]
        , "InstrumentName": instrumentNames[i]
        , "Duration": durations[i]
        , "Velocity": velocities[i]})
    rhythms.append(eventList) #add list of events to rhythms list (list in list)
    return rhythms

#Function that asks to start the sequencer and rate the individual rhythms
def rateNewRhythm():
    global isPlaying #global since we want to change this in playSequencer() to stop the sequencer
    threads = [ #create objects for the thread class
    myThread(0, "Rhythm-1", 0),
    myThread(1, "Rhythm-2", 1),
    myThread(2, "Rhythm-3", 2),
    myThread(3, "Rhythm-4", 3),
    myThread(4, "Rhythm-5", 4)]
    startSequencer = askQuestion.askQuestion('bool', "\nStart Sequencer?[Y/n]", {'allowEmpty': False})
    ratings = []

    while startSequencer:
        rhythmIndexPlayer = 0 #indexer for the current rhythm playing
        ratingIndex = 0 #indexer for the rating of that rhythm
        while rhythmIndexPlayer < 5: #quit playing after all 5 rhythms are played
            isPlaying = True 
            threads[rhythmIndexPlayer].start() #start playSequencer thread
            ratings.insert(ratingIndex, askQuestion.askQuestion('int', f'\nRhythm {rhythmIndexPlayer+1} (rating 1 - 10)', {"Min": 1, "Max": 10}))
            isPlaying = False #set to false to end function playSequencer()
            threads[rhythmIndexPlayer].join() #when playSequencer() has ended, end the thread
            ratingIndex += 1
            rhythmIndexPlayer += 1
            continue
        else:
            print(f'\nRatings:\nRhythm 1: {ratings[0]}\nRhythm 2: {ratings[1]}\nRhythm 3: {ratings[2]}\nRhythm 4: {ratings[3]}\nRhythm 5: {ratings[4]}\n')
            isPlaying = False #stop sequencer
            return ratings #return ratings, will be input for naturalSelection() function
    else:
        exit()

#function to play the audio (Event Handler)
def playSequencer(rhythmEvents):
    startTime = time.time()
    index = 0
    bar = 1
    print("\n")
    while True:
        timer = time.time() - startTime
        if index < len(rhythmEvents):  
            if timer > rhythmEvents[index]["Timestamp"]: #trigger sample if timestamp = timer
                rhythmEvents[index]["Sample"].play()
                if rhythmEvents[index]["Sixteenth"] > sixteenthAmount*bar:
                        # print(f'\nBar {bar+1}') #leave a blank line for every bar        
                        bar += 1 
                index += 1              
        else:
            if timer > sequenceLength:
                index = 0
                startTime = time.time()
                bar = 1
                # print("\nBar 1")
        if not isPlaying:
            break #break while loop if user exits sequencer  

        time.sleep(0.001) #Reduce CPU usage

#class for threads with run() function to execute playSequencer()function
class myThread(threading.Thread):
  # constructor calls threading init
  def __init__(self,threadID,name,ratingIndex):
    threading.Thread.__init__(self)
    self.threadID = threadID
    self.name = name
    self.ratingIndex = ratingIndex
    self.rhythmEvents = rhythms[self.threadID]
  # run() contains the code that performs the thread's tasks
  def run(self):
    print(f'Rhythm {self.threadID+1} now playing...')
    playSequencer(self.rhythmEvents)

#function that selects the 2 (or less) most favorite rhythms
def naturalSelection(ratings): 
    selectedRhythms = []

    for i in range(len(ratings)):
        if ratings[i] > 5: #only select rhythm if it has a higher rating than 5
            selectedRhythms.append({"Rhythm": i, "Rating": ratings[i]})

    if len(selectedRhythms) == 0:
        print("\nSorry.. i'll try to make better beats now...")
        time.sleep(1)
    elif len(selectedRhythms) == 1:
        print("\nAt least there's one you liked...")
        time.sleep(1)
    elif len(selectedRhythms) == 2:
        print("\nCreating babies with your favorite rhythms..")
        time.sleep(1)
    elif len(selectedRhythms) > 3:
        print("i see you're liking this... There's more from where that came from")
        time.sleep(1)
    
    def sortRating(rhythmsList):
        return rhythmsList["Rating"]
    
    selectedRhythms.sort(key=sortRating, reverse=True) #sort the selected rhythms based on rating
    return selectedRhythms

#function that creates new rhythm properties based on the favorite rhythms
def mutationProcess(parentRhythms):
    newProperties = [] #will be output of function
    if len(parentRhythms) == 0: #if there are no good rhythms create completely (random) new ones
        rhythmProperties.clear()

        for i in range(5):
            newProperties.append({
            "syncopation": random.random(), 
            "beatRepetition": random.random(), 
            "density": random.random(),
            "firstBeat": random.random(),
            "randomFill": random.random()})
        return newProperties
    
    if len(parentRhythms) == 1: #if only 1 good rhythm, make 3 new rhythms based on that one and 2 random ones
        ratingDelta = 10 - parentRhythms[0]["Rating"] #10 is highest rating
        randomRange = ratingDelta + 1 #+1 so we always have some range

        oldProperties = [] #list that contains properties of best rhythm of current generation
        for property in rhythmProperties[parentRhythms[0]["Rhythm"]]:
            oldProperties.append(rhythmProperties[parentRhythms[0]["Rhythm"]][property])
        
        rhythmProperties.clear() #clear old properties

        for i in range(3): #create 3 rhythms based on parent
            newProperties.append({
            "syncopation": ((random.randint(0, randomRange) / 10)+1) * oldProperties[0], 
            "beatRepetition": ((random.randint(0, randomRange) / 10)+1) * oldProperties[1], 
            "density": ((random.randint(0, randomRange) / 10)+1) * oldProperties[2],
            "firstBeat": ((random.randint(0, randomRange) / 10)+1) * oldProperties[3],
            "randomFill": ((random.randint(0, randomRange) / 10)+1) * oldProperties[4]})
        
        for i in range(2):
            newProperties.append({
            "syncopation": random.random(), 
            "beatRepetition": random.random(), 
            "density": random.random(),
            "firstBeat": random.random(),
            "randomFill": random.random()})
        return newProperties

    if len(parentRhythms) >= 2: #if we have 2 or more good rhythms

        parentProperties = []
        parent1Properties = []

        for property in rhythmProperties[parentRhythms[0]["Rhythm"]]:
            parentProperties.append(rhythmProperties[parentRhythms[0]["Rhythm"]][property])
        
        for property in rhythmProperties[parentRhythms[1]["Rhythm"]]:
            parent1Properties.append(rhythmProperties[parentRhythms[1]["Rhythm"]][property])

        parentsDelta = []
        for i in range(len(parentProperties)):
            parentsDelta.append(parent1Properties[i] - parentProperties[i])

        rhythmProperties.clear() #remove old properties

        #Parabolic equation so that the change of the child properties is likely to be of the parent with the higher rating
        #(ValueParent1 - ValueParent) * random.random() ** ((Rating1/Rating2)*SlopeFactor) + ValueParent1 
        slopeFactor = 1.5 #slopeFactor is the steepness of the parabolic function
        for i in range(5):
            newProperties.append({ #create 5 new rhythms with mixed propterties of parents
            "syncopation": parentsDelta[0]*(random.random()**((parentRhythms[0]["Rating"] / parentRhythms[1]["Rating"])*slopeFactor)) + parentProperties[0],
            "beatRepetition": parentsDelta[1]*(random.random()**((parentRhythms[0]["Rating"] / parentRhythms[1]["Rating"])*slopeFactor)) + parentProperties[1], 
            "density": parentsDelta[2]*(random.random()**((parentRhythms[0]["Rating"] / parentRhythms[1]["Rating"])*slopeFactor)) + parentProperties[2],
            "firstBeat": parentsDelta[3]*(random.random()**((parentRhythms[0]["Rating"] / parentRhythms[1]["Rating"])*slopeFactor)) + parentProperties[3],
            "randomFill": parentsDelta[4]*(random.random()**((parentRhythms[0]["Rating"] / parentRhythms[1]["Rating"])*slopeFactor)) + parentProperties[4]}
            )
        return newProperties

def storeToMidi(rhythmChoice):
    newMidiFile = MIDIFile(1) #midifile with 1 track
    track = 0
    channel = 0
    for event in rhythms[rhythmChoice]: #for the events in the chosen rhythm
        if event["InstrumentName"] == "Kick":
            pitch = 60
        elif event["InstrumentName"] == "Snare":
            pitch = 61
        elif event["InstrumentName"] == "HiHat":
            pitch = 62
        
        time = (event["Sixteenth"] -1) / 4 #timestamp in beats 
        duration = event["Duration"] / (60 / BPM) #duration in beats
        velocity = event["Velocity"]

        newMidiFile.addNote(track, channel, pitch, time, duration, velocity)

    outputFilePath = askQuestion.askQuestion('string', "\nEnter file name and/or directory ", {'allowEmpty': False, 'Max': 20}) + str(".mid") #create filename
    
    with open(outputFilePath, "wb") as output_file: #open and write to file
        newMidiFile.writeFile(output_file)
    
    return print(f'MIDI File created in {outputFilePath}')

for i in range (5):
    firstGen = createRhythm(
    random.random()
    , random.random()
    , random.random()
    , random.random()
    , random.random()) 
    createEvents(firstGen[0], firstGen[1], firstGen[2], firstGen[3], firstGen[4], firstGen[5])

ratings = rateNewRhythm()

while True: #While loop to keep creating new generations if user says so or to store to midi
    newGeneration = askQuestion.askQuestion('bool', "\nCreate a new generation?[Y/n]", {'allowEmpty': False})
    if newGeneration: #if user wants to create new generation
        newRhythmProperties = mutationProcess(naturalSelection(ratings)) #Create new rhythhm properties based on the selected rhythms
        rhythms.clear() #clear list with old rhythms
        for i in range(5):
            newGen = createRhythm(
            newRhythmProperties[i]["syncopation"], 
            newRhythmProperties[i]["beatRepetition"], 
            newRhythmProperties[i]["density"],
            newRhythmProperties[i]["firstBeat"],
            newRhythmProperties[i]["randomFill"])
            createEvents(newGen[0], newGen[1], newGen[2], newGen[3], newGen[4], newGen[5])
        ratings = rateNewRhythm() #Ask user to play and rate the new generation
        newGeneration = "" #initialize newGeneration and repaet While loop
        continue
    elif not newGeneration:
        midiStore = askQuestion.askQuestion('bool', "\nStore your favorite child to MIDI?[Y/n]", {'allowEmpty': False})
        if midiStore:
            chosenRhythm = askQuestion.askQuestion('int', "\nWhich child would you like to store to MIDI?", {'allowEmpty': False, 'Min': 1, 'Max': 5}) -1
            storeToMidi(chosenRhythm)
            break
        else:
            break