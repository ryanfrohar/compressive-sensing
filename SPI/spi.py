#!/usr/bin/env python3

import RPi.GPIO as GPIO
from time import sleep

MOSI = 19
MISO = 21
SCLK = 23
CE0 = 24
compressed = open("../Sampling/compressed.txt", "r")
phi = open("../Sampling/phi.txt", "r")
approx = open("approximation.txt", "w+")


def initspi():
    GPIO.setmode(GPIO.BOARD)
    GPIO.setwarnings(False)
    GPIO.setup(MOSI, GPIO.OUT)
    GPIO.setup(MISO, GPIO.IN)
    GPIO.setup(SCLK, GPIO.OUT)
    GPIO.setup(CE0, GPIO.OUT)
    
def sendbyte(cc):
    GPIO.output(CE0, GPIO.HIGH)
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
    GPIO.output(CE0, GPIO.HIGH)
    

def receivebyte():
    GPIO.output(SCLK, GPIO.LOW)
    GPIO.output(CE0, GPIO.LOW)
    out= 0b0
    #read 8 bits in MISO
    for x in range(8):
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
            
        linesPhi= phi.readlines()
        for lineP in linesPhi:
            sendbyte(int(lineP))
        
        sleep(40)
        approximation = []
       
        for x in range(0, 257):
            approximation.append(receivebyte())
            if x!=0:
                approx.write(str(approximation[x]) + "\n")
        
        
            
    except KeyboardInterrupt:  # When 'Ctrl+C' is pressed, the child program destroy() will be  executed.
        destroy()
