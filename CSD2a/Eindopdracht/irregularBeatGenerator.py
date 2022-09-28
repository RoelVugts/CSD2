import simpleaudio as sa
import random


kick = sa.WaveObject.from_wave_file("audioFiles/Kick.wav")
snare = sa.WaveObject.from_wave_file("audioFiles/Snare.wav")

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
    timeQuarterNote = 60 / BPM #calculate time (in seconds) per quarter note
    noteRatios = [1, 0.5, 0.25] #Quarter-, eight- and sixteenth -notes
    sequenceLength = timeQuarterNote * (4 * 4) #Set sequence length to 4 bars

    timestamps = [] #create array for timestamps
    timestamps.clear() #clear array if re-running function
    timestamps.append(0.0) #first timestamp starts always at 0.0 seconds

    while timestamps[-1] < sequenceLength: #create timestamps for x amount of time (sequenceLength)
        randomNoteValue = timeQuarterNote * noteRatios[random.randint(0, len(noteRatios) -1)] #choose a random note value
        if (randomNoteValue + timestamps[-1]) < sequenceLength: #if timestamp does not exceed sequenceLength --> add to array
            timestamps.append(randomNoteValue + timestamps[-1]) #add notevalue to last timestamp to move forward in time
            print(f'Timestamps: {timestamps[-1]}')
        else:
            print(f'\nCreated {len(timestamps)} timestamps!')
            return timestamps


createTimestamps()
