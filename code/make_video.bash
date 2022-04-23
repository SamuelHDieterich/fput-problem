#!/bin/bash

# Generate the video file from the PNG images on the img folder

ffmpeg -r 120 -i ../img/fput%d.png -vcodec libx264 -crf 25 -pix_fmt yuv420p ../video/output.mp4