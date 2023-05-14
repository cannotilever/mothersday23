from adafruit_servokit import ServoKit
import time
import requests

hat = ServoKit(channels=16)
print("program startup")
progress = 0

hat.servo[1].angle = 75 #door
hat.servo[0].angle = 0 #code

while True:
    time.sleep(2)
    rqst = requests.get("http://192.168.10.15/status")
    if (rqst.status_code != 200):
        print("Request failed!!")
        continue
    try:
        progress = int(rqst.content.decode('utf-8'))
    except(ValueError):
        print("Bad value from server! {}",rqst.content)
        continue
    # raspbian packages an ancient version of python so no switch :(
    if progress == 4:
        hat.servo[0].angle = 180
        
    elif progress == 5:
        hat.servo[1].angle = 180

