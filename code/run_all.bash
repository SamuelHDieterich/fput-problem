#!/bin/bash

# Run all the scripts
# Compile the C code -> Run the executable -> Run the gnuplot script -> Create the video file from the images on the img folder

gcc -lm fput.c 
./a.out
gnuplot graph.plt
./make_video.bash