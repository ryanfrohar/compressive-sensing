#!/usr/bin/env python3

import RPi.GPIO as GPIO
from time import sleep

samplingPin = 18
numSamples = 256
file = open("samples.txt", "w+")
sample = 0

def setup():
    print ('Program is starting...')
    GPIO.setmode(GPIO.BCM)       # Numbers GPIOs by physical location
    GPIO.setup(samplingPin, GPIO.IN)    # Set buttonPin's mode is input, and pull up to high level(3.3V)

def loop():
    last=0
    for x in range(numSamples):
        if GPIO.input(samplingPin):
            if last==0:
                sample = 1
                last = sample
                file.write(str(sample) + '\n')
            sleep(0.05)
        else: 
            sample = 0
            last=sample
            sleep(0.01)
            file.write(str(sample) + '\n')

def destroy():
    file.close()
    GPIO.cleanup()                     # Release resource

if __name__ == '__main__':     # Program start from here
    setup()
    try:
        loop()
    except KeyboardInterrupt:  # When 'Ctrl+C' is pressed, the child program destroy() will be  executed.
        destroy()

