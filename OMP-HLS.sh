#!/bin/bash
#Interactive shell script that allows developpers to run OMP script
gcc randomGenerator.c -o rand -lm
gcc OMP-HLS-Sparsity15.c -o OMPTest -lm
./rand
./OMPTest