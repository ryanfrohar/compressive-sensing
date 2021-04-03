#!/usr/bin/env python3

import RPi.GPIO as GPIO
from time import sleep

MOSI = 5
MISO = 10
SCLK = 15
CE0 = 7
compressed = open("../Sampling/compressed.txt", "r")
approx = open("approximation.txt", "w+")


def initspi():
    GPIO.setmode(GPIO.BOARD)
    GPIO.setwarnings(False)
    GPIO.setup(MOSI, GPIO.OUT)
    GPIO.setup(MISO, GPIO.IN)
    GPIO.setup(SCLK, GPIO.OUT)
    GPIO.setup(CE0, GPIO.OUT)
    
def sendbyte(cc):
    c='{0:08b}'.format(cc)
    bitsx = list(c)
    #Since list() returns String, must convert to integer for transmission
    for i in range (0, len(bitsx)):
        bitsx[i] = int(bitsx[i])

    GPIO.output(CE0, GPIO.LOW)
    #set MOSI signal level
    for x in range(8):
        if (bitsx[x]>0):
            GPIO.output(MOSI, GPIO.HIGH)
        else:
            GPIO.output(MOSI, GPIO.LOW)
        #clock    
        GPIO.output(SCLK, GPIO.LOW)
        GPIO.output(SCLK, GPIO.HIGH)
    GPIO.output(SCLK, GPIO.LOW)
    GPIO.output(SCLK, GPIO.HIGH)
    GPIO.output(CE0, GPIO.HIGH)
    

def receivebyte():
    GPIO.output(SCLK, GPIO.LOW)
    GPIO.output(CE0, GPIO.LOW)
    out= 0b0
    #read 8 bits in MISO
    for x in range(8):
        GPIO.output(SCLK, GPIO.LOW)
        GPIO.output(SCLK, GPIO.HIGH)
        out = out*2
        if GPIO.input(MISO):
            out = out +1
    GPIO.output(SCLK, GPIO.LOW)
    GPIO.output(SCLK, GPIO.HIGH)
    GPIO.output(CE0, GPIO.HIGH)
    return out

if __name__ == '__main__':     # Program start from here
    initspi()
    try:
        lines= compressed.readlines()
        for line in lines:
            sendbyte(int(line))
        
        
        sleep(300)
        approximation = []
       
        for x in range(0, 64):
            approximation.append(receivebyte())
            approx.write('%s\n' % approximation[x])
        
        
            
    except KeyboardInterrupt:  # When 'Ctrl+C' is pressed, the child program destroy() will be  executed.
        destroy()
