import mido
import os

termwidth = os.get_terminal_size()[0]

piano = mido.open_input('Steinberg UR22C:Steinberg UR22C MIDI 1 20:0')

print("=".center(termwidth, '='))
print("Happy Mother's Day!".center(termwidth))
print("\nWaiting for your input...")
while True:
    data = piano.poll()
    if data is None:
        continue
    
