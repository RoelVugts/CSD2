import simpleaudio as sa

repetitions = 0 #counter

wave_obj = sa.WaveObject.from_wave_file("audioFiles/TestKick.wav")
wave_obj1 = sa.WaveObject.from_wave_file("audioFiles/Heavy.wav") 
#wave_obj2 = sa.WaveObject.from_wave_file("audioFiles/Kloenk.wav") waarom werkt dit niet? omdat bitsnelheid anders is
wave_obj3 = sa.WaveObject.from_wave_file("audioFiles/Pitched.wav")
wave_obj4 = sa.WaveObject.from_wave_file("audioFiles/Rammel.wav")

playMode = int(input("Enter the kick you want to hear (1 - 5): "))

inputRepetitions = int(input("Enter amount of repetitions: "))

if playMode == 1:
    while repetitions < inputRepetitions:
        play_obj = wave_obj.play()
        play_obj.wait_done()
        repetitions = repetitions + 1

if playMode == 2:
    while repetitions < inputRepetitions:
        play_obj = wave_obj1.play()
        play_obj.wait_done()
        repetitions = repetitions + 1

if playMode == 3:
    while repetitions < inputRepetitions:
        play_obj = wave_obj2.play()
        play_obj.wait_done()
        repetitions = repetitions + 1

if playMode == 4:
    while repetitions < inputRepetitions:
        play_obj = wave_obj3.play()
        play_obj.wait_done()
        repetitions = repetitions + 1

if playMode == 5:
    while repetitions < inputRepetitions:
        play_obj = wave_obj4.play()
        play_obj.wait_done()
        repetitions = repetitions + 1
