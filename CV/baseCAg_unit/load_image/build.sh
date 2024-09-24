#!/bin/bash
g++ loadImage.cpp -o loadImage `pkg-config --cflags --libs opencv` 
echo "build finush, excution application now!"
