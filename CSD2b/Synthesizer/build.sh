#!/bin/bash

rm output.csv
make clean

make
clear
./Synth

python3 plot.py