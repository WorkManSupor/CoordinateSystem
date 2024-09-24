#!/bin/bash
g++ setImageSize.cpp -o setImageSize `pkg-config --cflags --libs opencv` 
echo "build finish, excution application now!"
