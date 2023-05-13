# Mother's Day '23 Design Document

## Outline

Hand her handheld device (breadboard with ESP32, power bank, LEDs, and OLED) which displays "happy Mother's day!" on it. When she turns the on-board potentiometer, it displays a clude to the first qr code.

Scavenger hunt, making use of QR codes which link back to a local webserver which incriments a count on every qr code call, displays a hint to the next code's location.

on activation of last code, cardboard box of mystery opens, romi drives out with chocolates mounted on top. Romi drives around, avoiding collision with ultrasonic rangefinder until she catches it.

## Scavenger hunt

### Tag 1 - Microwave

Hint given by handheld device

Hint: "I contain waves but have no water"

Tag content: `/tag/love`

### Tag 2 - weird overhead thing in patio

Hint given by previous tag

Hint: "No one really knows just what I am, neither do I most days. It's okay thoug, I'm just happy to hang out here."

### Tag 3 - blue croquet mallet

Hint given by previous tag

Hint: "Is golf too interesting for you? There's no need to feel blue, I think we'll hit it off just fine and have a smashing time!"

### MIDI

Hint given by previous tag

Hint: "I have a striking similarity to locks and laptops though I am neither. I am also the oldest electronic device in the house."

have her play a sequence of notes

raspi running ubuntu

issues a GET request to the server to incriment tag count w/o actual qr code

### Tag 4 - Top of box

Hidden under servo controller piece of cardboard.

Hint: "go check the box"


## Webserver

A rust server built with the rocket framework 
