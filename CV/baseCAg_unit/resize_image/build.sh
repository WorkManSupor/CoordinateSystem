#!/bin/bash
g++ resizeImage.cpp -o resizeImage `pkg-config --cflags --libs opencv` 
echo "build finish, excution application now!"
