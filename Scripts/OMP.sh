#!/bin/bash
#Interactive shell script that allows developpers to run OMP script
cd ../Testing/
gcc randomGenerator.c -o rand -lm
./rand
cd ../C/
gcc phiGenerator.c -o phi -lm
./phi
gcc -o testbench testbench.c OMP.c -lm
./testbench
