#!/bin/bash
#Interactive shell script that allows developpers to run OMP script
cd ../Testing/
gcc randomGenerator.c -o rand -lm
./rand
cd ../C/
gcc OMP.c -o OMP -lm
./OMP
