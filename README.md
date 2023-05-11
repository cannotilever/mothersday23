# Mother's Day '23 Design Document

## Outline

Hand her handheld device (breadboard with ESP32, power bank, LEDs, and OLED) which displays "happy Mother's day!" on it. When she turns the on-board potentiometer, it displays a clude to the first qr code.

Scavenger hunt, making use of QR codes which link back to a local webserver which incriments a count on every qr code call, displays a hint to the next code's location.

on activation of last code, cardboard box of mystery opens, romi drives out with chocolates mounted on top. Romi drives around, avoiding collision with ultrasonic rangefinder until she catches it.

## Scavenger hunt

### MIDI
Remember to use: `mido.open_input('Steinberg UR22C:Steinberg UR22C MIDI 1 20:0')`
have her play a sequence of notes

running ubuntu desktop
