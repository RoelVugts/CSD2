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
beatValue = askQuestion.askQuestion('int', "\nPlease enter the note value counted as beat(4/8/16)", {'allowEmpty': False, 'Choices': [4, 8 ,16]})


#Global variables
#----------------------------------------
timeQuarterNote = (60 / BPM)   #calculate time (in seconds) per qnote counted as beat
noteRatios = [1, 0.5, 0.25] #Quarter-, eight- and sixteenth -notes
sequenceLength = (timeQuarterNote / (beatValue/4)) * beatsPerMeasure*4 #Length of 4 bars in seconds
sixteenthAmount = int(beatsPerMeasure / (beatValue/16)) #total amount of sixteenths in 1 bar


rhythmProperties = [] #list to store properties of each rhythm
rhythms = [] #list to store 5 rhythms that will be generated
eventList = [] #list to store all the events within a rhythm

#Properties of rhythm
#-------------------------
#Syncope = Kans dat er geen sample op de tel wordt gespeeld
#repetition = hoe veel kans er is dat beat zich herhaalt (zowel ritme als instrumenten)
#density = hoe veel noten er in een beat zitten
#firstBeat = Kans dat iets op de eerste tel valt

#Function to generate properties of a rhythm
def createRhythmProperties(syncopation, beatRepetition, density, firstBeat, randomFill):
    rhythmProperties.append({"syncopation": round(syncopation,4), "beatRepetition": round(beatRepetition,4), "density": round(density,4), "firstBeat": round(firstBeat,4), "randomFill": round(randomFill,4)})
    #print(f'Syncopation: {rhythmProperties[-1]["syncopation"]} ; beatRepetition: {rhythmProperties[-1]["beatRepetition"]} ; density: {rhythmProperties[-1]["density"]} ; firstBeat: {rhythmProperties[-1]["firstBeat"]} ; randomFill: {rhythmProperties[-1]["randomFill"]}')

#function that creates 4 bar rhythm based on properties
def createRhythm(rhythmIndex):
    global sixteenths #global variables since there used on several places in the code
    global timestamps
    global durations
    global instruments
    global instrumentNames
    global stampsOneBar

    #clear all lists when re-running function
    timestamps = []
    timestamps.clear() 

    durations = [] 
    durations.clear()

    sixteenths = []
    sixteenths.clear()

    instruments = []
    instruments.clear()

    instrumentNames = []
    instrumentNames.clear()

    barIndex = 0 #keeps count of how many bars we have created
    
    def createOneBar():
        randomPosNeg =[1, -1] #list for deciding if syncopated offset is before or after the beat/pulse

        for i in range(0, int((sixteenthAmount))):
            if (i+(barIndex*sixteenthAmount)) % sixteenthAmount == 0:
                if random.random() < rhythmProperties[rhythmIndex]["firstBeat"]: #Chance a stamp is on first beat
                    sixteenths.append(1 + (barIndex * sixteenthAmount)) #add to first beat of bar
                    instruments.append(kick)
                    instrumentNames.append(("Kick"))
            elif i % (sixteenthAmount/beatsPerMeasure) == 0 and i != 0: #for every beat thats not the first beat
                randomSyncope = random.random()
                if randomSyncope < rhythmProperties[rhythmIndex]["syncopation"] and randomSyncope < rhythmProperties[rhythmIndex]["density"]: #if syncopation is high (1.0) create a syncopation  
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
                if random.random() < rhythmProperties[rhythmIndex]["density"]: #create stamp in between beats if density is high
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
        if i != 3 or random.random() > rhythmProperties[rhythmIndex]["randomFill"]: #if true do not create fill
            if random.random() < rhythmProperties[rhythmIndex]["beatRepetition"]: #if true then repeat first bar
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


    sixteenths.sort()

    for sixteenth in sixteenths: #convert sixteenths to timestamps
        timestamps.append(round((((sixteenth-1)/(sixteenthAmount*4)) * sequenceLength),4))
        
    for i in range(len(timestamps)): #create durations (for midi output file)
        if i+1 < len(timestamps):
            durations.append(timestamps[i+1] - timestamps[i])
        else:
            durations.append(sequenceLength - timestamps[i])

#function to create velocites (for MIDI File)
def createVelocities():
    global velocities
    velocities = []
    velocities.clear()

    for i in range(len(sixteenths)): #create instruments for first bar
        if (sixteenths[i]) % beatValue == 1:
            randomVel = random.randint(100, 127)
            velocities.append(randomVel)
        else:
            randomVel = random.randint(40, 70)
            velocities.append(randomVel)

#function that creates events in a dictionar of a rhythm
def createEvents(eventList): #list is a parameter since we will make a separate list per rhythm
    eventList = []
    eventList.clear()

    for i in range(len(timestamps)): #for loop to push individual arrays in dictionary
        eventList.append({"Timestamp" : timestamps[i]
        , "Sixteenth": sixteenths[i]
        , "Sample": instruments[i]
        , "InstrumentName": instrumentNames[i]
        , "Duration": durations[i]
        , "Velocity": velocities[i]})
    rhythms.append(eventList) #add list of events to rhythms list (list in list)


#function that executes above functions
def createNewBeat(): 
    print("\nGave birth to 5 new rhytms!")
    print("\nPlease rate the rhythms and let only the best ones create new baby rhythms!")
    rhythms.clear()
    for rhythmIndex in range(len(rhythmProperties)): 
        createRhythm(rhythmIndex)
        createVelocities()
        createEvents(rhythmIndex)
    print("\n")

#Function that asks to start the sequencer and rate the individual rhythms
def playNewRhythm():
    global isPlaying
    global ratings
    global threads
    threads = [ #create objects for the thread class
    myThread(0, "Rhythm-1", 0),
    myThread(1, "Rhythm-2", 1),
    myThread(2, "Rhythm-3", 2),
    myThread(3, "Rhythm-4", 3),
    myThread(4, "Rhythm-5", 4)]
    startSequencer = askQuestion.askQuestion('bool', "\nStart Sequencer?[Y/n]", {'allowEmpty': False})
    ratings = []
    ratings.clear()
    while startSequencer:
        rhythmIndexPlayer = 0 #indexer for the current rhythm playing
        ratingIndex = 0 #indexer for the rating of that rhythm
        while rhythmIndexPlayer < 5: #quit playing after all 5 rhythms are played
            isPlaying = True 
            threads[rhythmIndexPlayer].start() 
            ratings.insert(ratingIndex, askQuestion.askQuestion('int', f'\nRhythm {rhythmIndexPlayer+1} (rating 1 - 10)', {"Min": 1, "Max": 10}))
            if ratings[ratingIndex]:
                isPlaying = False
                threads[rhythmIndexPlayer].join()
                ratingIndex += 1
                rhythmIndexPlayer += 1
                continue
        else:
            print(f'\nRatings:\nRhythm 1: {ratings[0]}\nRhythm 2: {ratings[1]}\nRhythm 3: {ratings[2]}\nRhythm 4: {ratings[3]}\nRhythm 5: {ratings[4]}\n')
            break
    else:
        exit()

#function to play the audio (Event Handler)
def playSequencer(rhythmIndex):
    startTime = time.time()
    index = 0
    bar = 1
    print("\n")
    while True:
        timer = time.time() - startTime
        if index < (len(rhythms[rhythmIndex])):  
            if timer > rhythms[rhythmIndex][index]["Timestamp"]: #trigger sample if timestamp = timer
                rhythms[rhythmIndex][index]["Sample"].play()
                if rhythms[rhythmIndex][index]["Sixteenth"] > sixteenthAmount*bar:
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


#class for threads with run() function to execute playSequencer() function
class myThread(threading.Thread):
  # constructor calls threading init
  def __init__(self,threadID,name,ratingIndex):
    threading.Thread.__init__(self)
    self.threadID = threadID
    self.name = name
    self.ratingIndex = ratingIndex
  # run() contains the code that performs the thread's tasks
  def run(self):
    print(f'Rhythm {self.threadID+1} now playing...')
    playSequencer(self.threadID)
    global rating

#function that selects the 2 (or less) most favorite rhythms
def naturalSelection(): 
    global selectedRhythms
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
    elif len(selectedRhythms) > 2:
        print("i see you're liking this... There's more from where that came from")
        time.sleep(1)
    
    def sortRating(rhythmsList):
        return rhythmsList["Rating"]
    
    selectedRhythms.sort(key=sortRating, reverse=True) #sort the selected rhythms based on rating


#function that creates new rhythm properties based on the favorite rhythms
def mutationProcess():
    if len(selectedRhythms) == 0: #if there are no good rhythms create completely (random) new ones
        print("Drol")
        rhythmProperties.clear()
        for i in range(5):
            createRhythmProperties(
              random.random()
            , random.random()
            , random.random()
            , random.random()
            , random.random())
    
    if len(selectedRhythms) == 1: #if only 1 good rhythm, make 3 new rhythms based on that one and 2 random ones
        ratingDelta = 10 - selectedRhythms[0]["Rating"] #10 is highest rating
        randomRange = ratingDelta + 1 #+1 so we always have some range
        
        print(f'sel: {selectedRhythms}')
        print(f' selected: {rhythmProperties[selectedRhythms[0]["Rhythm"]]}')

        oldProperties = [
            rhythmProperties[selectedRhythms[0]["Rhythm"]]["syncopation"]
        , rhythmProperties[selectedRhythms[0]["Rhythm"]]["beatRepetition"]
        , rhythmProperties[selectedRhythms[0]["Rhythm"]]["density"]
        , rhythmProperties[selectedRhythms[0]["Rhythm"]]["firstBeat"]
        , rhythmProperties[selectedRhythms[0]["Rhythm"]]["randomFill"]
        ]
        
        rhythmProperties.clear() #clear old properties

        for i in range(3): #create 3 rhythms
            createRhythmProperties(
                ((random.randint(0, randomRange) / 10)+1) * oldProperties[0]
            ,   ((random.randint(0, randomRange) / 10)+1) * oldProperties[1]
            ,   ((random.randint(0, randomRange) / 10)+1) * oldProperties[2]
            ,   ((random.randint(0, randomRange) / 10)+1) * oldProperties[3]
            ,   ((random.randint(0, randomRange) / 10)+1) * oldProperties[4]
            )
        
        for i in range(2): #create 2 random rhythms
            createRhythmProperties(
              random.random()
            , random.random()
            , random.random()
            , random.random()
            , random.random())

    if len(selectedRhythms) >= 2: #if we have 2 or more good rhythms
     
        parentSyncopation = rhythmProperties[selectedRhythms[0]["Rhythm"]]["syncopation"]
        parentRepetition= rhythmProperties[selectedRhythms[0]["Rhythm"]]["beatRepetition"]
        parentDensity = rhythmProperties[selectedRhythms[0]["Rhythm"]]["density"]
        parentFirstBeat = rhythmProperties[selectedRhythms[0]["Rhythm"]]["firstBeat"]
        parentRandomFill = rhythmProperties[selectedRhythms[0]["Rhythm"]]["randomFill"]

        parent1Syncopation = rhythmProperties[selectedRhythms[1]["Rhythm"]]["syncopation"]
        parent1Repetition= rhythmProperties[selectedRhythms[1]["Rhythm"]]["beatRepetition"]
        parent1Density = rhythmProperties[selectedRhythms[1]["Rhythm"]]["density"]
        parent1FirstBeat = rhythmProperties[selectedRhythms[1]["Rhythm"]]["firstBeat"]
        parent1RandomFill = rhythmProperties[selectedRhythms[1]["Rhythm"]]["randomFill"]

        #Misschien niet kiezen tussen 2 maar ergens tussenin pakken? dichterbij waarde pakken van hogere rating
        syncopationGenome = abs((parentSyncopation - parent1Syncopation))
        repetitionGenome = abs(parentRepetition - parent1Repetition)
        densityGenome = abs(parentDensity - parent1Density)
        firstBeatGenome = abs(parentFirstBeat - parent1FirstBeat)
        randomFillGenome = abs(parentRandomFill - parent1RandomFill)

        rhythmProperties.clear() #remove old properties
        for i in range(5):
            createRhythmProperties( #create 5 new rhythms with mixed propterties of parents
            random.random() * syncopationGenome +  min([parentSyncopation, parent1Syncopation]),
            random.random() * repetitionGenome + min([parentRepetition, parent1Repetition]),
            random.random() * densityGenome + min([parentDensity, parent1Density]),
            random.random() * firstBeatGenome + min([parentFirstBeat, parent1FirstBeat]),
            random.random() * randomFillGenome + min([parentRandomFill, parent1RandomFill])
            )

def storeToMidi(rhythmChoice):
    newMidiFile = MIDIFile(1) #midifile with 1 track
    track = 0
    channel = 0
    for event in rhythms[rhythmChoice]: #for the events in hte chosen rhythm
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

    outputFilePath = askQuestion.askQuestion('string', "\nEnter file name and/or directory ", {'allowEmpty': False, 'Max': 20}) + str(".mid") #create filename
    
    with open(outputFilePath, "wb") as output_file: #open and write to file
        newMidiFile.writeFile(output_file)
    
    return print(f'MIDI File created in {outputFilePath}')


#create first generation
rhythmProperties.clear()
for i in range (5):
    createRhythmProperties(
      random.random()
    , random.random()
    , random.random()
    , random.random()
    , random.random()) 

createNewBeat()
playNewRhythm()


while True: #While loop to keep creating new generations if user says so or to store to midi
    newGeneration = askQuestion.askQuestion('bool', "\nCreate a new generation?[Y/n]", {'allowEmpty': False})
    if newGeneration: #if user wants to create new generation
        naturalSelection() #select best rhythms from current generation
        mutationProcess() #Create new rhythhm properties based on the selected rhythms
        createNewBeat() #Create the actual rhythms (timestamps, dur, instruments)
        playNewRhythm() #Ask user to play and rate the new generation
        newGeneration = ""
        continue
    elif not newGeneration:
        midiStore = askQuestion.askQuestion('bool', "Store your favorite child to MIDI?[Y/n]", {'allowEmpty': False})
        if midiStore:
            chosenRhythm = askQuestion.askQuestion('int', "Which child would you like to store to MIDI?", {'allowEmpty': False, 'Min': 1, 'Max': 5}) -1
            storeToMidi(chosenRhythm)
            break
        else:
            break




























# threadIndex = 0
# t = []

# def startThread(rhythmIndex): #function to create a new thread when restarting sequencer
#     global threadIndex
#     global t
#     t.append(threading.Thread(target=playSequencer, args=(rhythmIndex,))) #waarom die komma?!
#     t[threadIndex].start()

# def stopThread(): #function to stop current thread
#     global threadIndex
#     if threading.active_count() > 1: #check if there are more threads running than 1 (main thread)
#         t[-1].join() #close thread if thread is active
#         threadIndex += 1 #move index up for restarting thread