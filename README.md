# Welcome to the Compressive-Sensing Project
## CONTENTS OF THIS FILE
* Introduction
* Requirements
* C
* HDL
* SPI
* Sampling
* Scripts
* Testing
* Execution
* Authors 

## INTRODUCTION
The Compressive Sensing project was developed as a fourth year capstone project at Carleton Univeristy by the authors listed at the end of this document. This project was developed over a span of 8 months with project planning, research and then development.

This ReadMe will walk you through the folders and files for the project as well as their functionalities and how to execute them.

## REQUIREMENTS
To run this project the user will require the following:
* Folders: C, HDL, Scripts, Testing, Sampling, SPI
* Programs: Terminal with gcc or other C executers
* Operating System: Mac, Windows, Linux
* Hardware: FPGA, RaspberryPi, Heart Rate Sensor  

## C
This folder is composed of multiple C files used to run the OMP alogorithm, generate random numbers for the input signal, and test that the algorithm outputs the results that are expected using testbench.

#### Files in the C folder:
* OMP.c - This file contains the C code which contains the implementation of the functions required for the OMP algorithm. 
* OMP.h - This is the header file for the OMP algorithm, it contains the initial definitions for the OMP.c file.
* OMP_NW.c-
* phiInput.c - Contains the function to implement the random matrix phi.
* phi.txt - This text file contain the compressed signal as one line. 
* phiGenerator.c -
* testbench.c - This file contains the test case used for the implementation of the OMP algorithm. Done by comparing the compressed signal with the undersampled one.

## HDL
This folder contains the files required to convert the OMP algorithm from C code to Verilog HDL in order to be implemented on to the FPGA.

#### Files in the HDL folder:
* .DS_Store -
* Arty-S7-50-Master.xdc - This is a contraint file which contains a list of the FPGA's pins which connect to the physical pin on the board.
* inputSensor.v - This file implements the input pin from which the FPGA is connect to the Raspberry Pi. 
* inputSensorTest.v -
* target.txt- 
* fpgaDesign.v -
* sending.v -
* signalProcess.v -
* target.txt -

## SPI
The SPI folder contains the files used for the implementation SPI protocol which allows for synchronous communication between the the RaspberryPi and FPGA.  

### Files in the SPI folder:
* approximation.txt -
* samples.txt - 
* spi.py - 

## Sampling
The Sampling folder contains the files required to

### Files in the Sampling folder:
* compressed.txt - This text file contains the compressed signal values. 
* compressedSamples.txt - 
* compressor.c - 
* phi.txt - 
* phiGenerator.c - 
* samples.txt - 
* sampling.py - 

## TESTING
The testing folder conatins the input signal from the heart rate sensor and the random generator which are used as inputs for the OMP algorithm.

#### Files in the Testing folder:
* inputSignal.dat - 
* inputSignal.txt -
* randomGenerator.c -
* inputSignal.txt - 

## Execution


## AUTHORS
* Archit Bhatia
* Marko Simic
* Ross Matthew
* Ryan Frohar
