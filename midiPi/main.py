import mido
import os
import time
import requests
termwidth = os.get_terminal_size()[0]

piano = mido.open_input('Steinberg UR22C:Steinberg UR22C MIDI 1 24:0')

# smoke on the water, last value should never be read, just filler
noteArray = [3, 6, 8,  3, 6, 9, 8,  3, 6, 8, 6, 3, 3, 0]
noteIndex = 0
keyHeld = False
printTimer = time.time()
print("=".center(termwidth, '='))
print("Happy Mother's Day!".center(termwidth))
print("\n I heard there was some stupid with a flare gun.")
print("Waiting for your input...\n")

def handleWin():
    print("Good job!")
    requests.post("http://192.168.10.15/tag/piano")
    print("Go check the box.")
    time.sleep(15)
    os.system("poweroff")

while True:
    if (time.time() - printTimer > 0.5):
        progressBar = "[" + "#"*noteIndex + "-"*(13-noteIndex) + "]"
        print(progressBar.center(termwidth), end='\r')
        if noteIndex == 13:
            time.sleep(0.25)
            handleWin()
            break
        printTimer=time.time()
    data = piano.poll()
    if data is None:
        continue
    if data.type != 'note_on':
        continue
    if data.velocity == 0:
        keyHeld = False
        continue
    if keyHeld:
        continue
    keyHeld = True
    note = data.note%12 #make it octave agnostic
    if (note == noteArray[noteIndex]):
        noteIndex += 1
        printTimer=0
    else:
        noteIndex = 0
