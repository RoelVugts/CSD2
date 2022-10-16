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
sequenceLength = (timeQuarterNote / (beatValue/4)) * beatsPerMeasure*4 #Length of 4 bars in seconds
sixteenthAmount = int(beatsPerMeasure / (beatValue/16)) #total amount of sixteenths in 1 bar
# print(f'SequenceLength:  = {timeQuarterNote} / ({beatValue}/4) * {beatsPerMeasure} * 4 = {sequenceLength}')
# print(f'Sixteenths: {sixteenthAmount}')

rhythmProperties = [] #list to store properties of each rhythm
#Properties of rhythm
# rhythms.append({"syncopation": 0.6, "beatRepetition": 1.0, "Density": 0.2, "firstBeat": 0.8, "randomFill": 1.0})
# print(f'Syncopation: {rhythms[0]["syncopation"]} ; beatRepetition: {rhythms[0]["beatRepetition"]} ; Density: {rhythms[0]["Density"]} ; firstBeat: {rhythms[0]["firstBeat"]} ; randomFill: {rhythms[0]["randomFill"]}')

#Syncope = Kans dat er geen sample op de tel wordt gespeeld
#repetition = hoe veel kans er is dat beat zich herhaalt (zowel ritme als instrumenten)
#density = hoe veel noten er in een beat zitten
#firstBeat = Kans dat iets op de eerste tel valt

for i in range(5): #give birth to 5 rhytms
    rhythmProperties.append({"syncopation": random.random(), "beatRepetition": random.random(), "Density": random.random(), "firstBeat": random.random(), "randomFill": random.random()})

print("Gave birth to 5 new rhytms!")
print("Please rate the rhythms and let only the best ones create new baby rhythms")


def createRhythm(rhythmIndex):
    global sixteenths
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
        randomPosNeg =[1, -1]

        for i in range(0, int((sixteenthAmount))):
            if (i+(barIndex*sixteenthAmount)) % sixteenthAmount == 0:
                if random.random() < rhythmProperties[rhythmIndex]["firstBeat"]: #Chance a stamp is on first beat
                    sixteenths.append(1 + (barIndex * sixteenthAmount)) #add to first beat of bar
                    instruments.append(kick)
                    instrumentNames.append(("Kick"))
                    # print(f' FirstBeat: {1 + (barIndex * sixteenthAmount)}')
            elif i % (sixteenthAmount/beatsPerMeasure) == 0 and i != 0: #for every beat thats not the first beat
                randomSyncope = random.random()
                #print(f'randomSyncope {randomSyncope}')
                if randomSyncope < rhythmProperties[rhythmIndex]["syncopation"] and randomSyncope < rhythmProperties[rhythmIndex]["Density"]: #if syncopation is high (1.0) create a syncopation  
                    syncopatedStamp = random.randint(1,2) # add stamp with offset 1 or 2 sixteenths
                    if not sixteenths: #if list is empty
                        lastIndex = 0 #amount of indexes in list = 0
                    else:
                        lastIndex = sixteenths[-1] #if not empty set to last index in list
                    if (syncopatedStamp + lastIndex) <= (((barIndex+1)*sixteenthAmount)): # and syncopatedStamp + sixteenths[-1] in sixteenths:
                        sixteenths.append(i+1+(syncopatedStamp*random.choice(randomPosNeg)) + (barIndex * sixteenthAmount)) #Add stamp with positive or negative offset (syncopation)
                        # print(f'Syncope: {i+(syncopatedStamp*random.choice(randomPosNeg)) + (barIndex * sixteenthAmount)}')
                        randomSample = random.randint(0,1)
                        instruments.append(audioSamples[randomSample])
                        instrumentNames.append(instrumentStrings[randomSample])
                else: #if syncopation is low
                    sixteenths.append(i+1 + barIndex*sixteenthAmount) #add stamp on beat
                    # print(f'On Beat: {i+1 + barIndex*sixteenthAmount}')
                    randomSample = random.randint(0,1)
                    instruments.append(audioSamples[randomSample])
                    instrumentNames.append(instrumentStrings[randomSample])
            elif i % (sixteenthAmount/beatsPerMeasure) != 0 or (i+(barIndex*sixteenthAmount)) % sixteenthAmount == 0: #for every other position
                if random.random() < rhythmProperties[rhythmIndex]["Density"]: #create stamp in between beats if density is high
                    sixteenths.append(i+1 + (barIndex*sixteenthAmount))
                    # print(f'Dense: {i+1 + (barIndex*sixteenthAmount)}')
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

rhythms = [] #list to store 5 rhythms that will be generated
eventList = [] #list to store all the events within a rhythm

def createEvents(eventList): #add event info to dictionary in event array
    eventList = []
 
    # print(f'timestamps{len(timestamps)}')
    # print(f'Sixteenths: {len(sixteenths)}')
    # print(f'Samples: {len(instruments)}')
    # print(f'names: {len(instrumentNames)}')
    # print(f'Duration: {len(durations)}')
    # print(f'velocities: {len(velocities)}')
    for i in range(len(timestamps)): #for loop to push individual arrays in dictionary
        eventList.append({"Timestamp" : timestamps[i]
        , "Sixteenth": sixteenths[i]
        , "Sample": instruments[i]
        , "InstrumentName": instrumentNames[i]
        , "Duration": durations[i]
        , "Velocity": velocities[i]})
    rhythms.append(eventList) #add list of events to rhythms list (list in list)
        # print(f'Timestamp {i}: {events[i]["Timestamp"]:<8} ; Sixteenth: {events[i]["Sixteenth"]} ;  {events[i]["InstrumentName"]} ; Duration: {events[i]["Duration"]} ; Velocity: {velocities[i]}')


def createNewBeat(): #function that generates a new 4 bar rhythm
    for i in range(len(rhythmProperties)): 
        createRhythm(i)
        createVelocities()
        createEvents(i)
    print("\n")


createNewBeat()

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
                # if events[index]["Sample2"] != "Empty": #Play sample2 simultaneous if not empty
                #     events[index]["Sample2"].play()
                if rhythms[rhythmIndex][index]["Sixteenth"] > sixteenthAmount*bar:
                        # print(f'\nBar {bar+1}') #leave a blank line for every bar        
                        bar += 1 
                # print(f'Timestamp {index}: {eventList[index]["Timestamp"]} ; {eventList[index]["InstrumentName"]} Sixteenth: {eventList[index]["Sixteenth"]}')
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


threads = [
myThread(0, "Rhythm-1", 0),
myThread(1, "Rhythm-2", 1),
myThread(2, "Rhythm-3", 2),
myThread(3, "Rhythm-4", 3),
myThread(4, "Rhythm-5", 4)]


def storeToMidi():
    newMidiFile = MIDIFile(1) #midifile with 1 track
    track = 0
    channel = 0
    for event in eventList: #convert samples to midi pitch
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

startSequencer = askQuestion.askQuestion('bool', "Start Sequencer?[Y/n]", {'allowEmpty': False})
ratings = []

while startSequencer:
    rhythmIndexPlayer = 0 #indexer for the current rhythm playing
    ratingIndex = 0 #indexer for the rating of that rhythm
    while rhythmIndexPlayer < 5: #quit playing after all 5 rhythms are played
        isPlaying = True 
        threads[rhythmIndexPlayer].start() 
        ratings.insert(ratingIndex, askQuestion.askQuestion('int', f'Rhythm {rhythmIndexPlayer+1} (rating 1 - 10)', {"Min": 1, "Max": 10}))
        if ratings[ratingIndex]:
            isPlaying = False
            threads[rhythmIndexPlayer].join()
            ratingIndex += 1
            rhythmIndexPlayer += 1
            continue
    else:
        break
else:
    exit()

print(f'Ratings:\nRhythm 1: {ratings[0]}\nRhythm 2: {ratings[1]}\nRhythm 3: {ratings[2]}\nRhythm 4: {ratings[3]}\nRhythm 5: {ratings[4]}')

print("Generating new baby rhythms based on your ratings...")

def beatMutation():
    #hier moet een functie komen die de ratings en de eigenschappen van de ritmes combineert en nieuwe ritmes genereert.
    rhythmProperties[0]["syncopation"] * ratings[0]

    rhythmProperties.append({"syncopation": random.random(), "beatRepetition": random.random(), "Density": random.random(), "firstBeat": random.random(), "randomFill": random.random()})

    """
    Eigenschap1 ritme * rating + Eigenschap2 ritme * rating 
    
    
    
    
    """

# while True: #while loop with 2 while loops. 1. for asking to start or exit sequencer. 2. For store options or to create new beat, and then go back to while loop 1 --> start sequencer
#     if storeInput != "X" and storeInput != "Y": #if user input did not exit program than stay in while loop, else break
#         while True:
#             keyInput = input("\nGo = start sequencer\nX = exit sequencer\nN = Create New Beat\n> ")
#             if (keyInput == "Go"): 
#                 stopThread()  
#                 startThread() #create thread to start the sequencer
#             elif (keyInput == "X"):
#                 stopThread() #stop thread
#                 break
#             elif (keyInput == "N"):
#                 createNewBeat()
#             else:
#                 print("False input")
#                 continue

#         while True:
#             storeInput = input("\nWould you like to store this beat?\nY = Yes, store this beat!\nN = No, create a new beat\nX = Exit program\n> ")
#             if storeInput == "Y":
#                 storeToMidi()
#                 break
#             elif storeInput == "N":
#                 createNewBeat()
#                 break
#             elif storeInput == "X":
#                 break
#             else:
#                 print("False input\n")
#     else:
#         break





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