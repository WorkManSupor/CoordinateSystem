#!/bin/bash
g++ overTurnImage.cpp -o overTurnImage `pkg-config --cflags --libs opencv` 
echo "build finish, excution application now!"
