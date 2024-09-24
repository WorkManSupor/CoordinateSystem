#!/bin/bash
g++ cutImage.cpp -o cutImage `pkg-config --cflags --libs opencv` 
echo "build finish, excution application now!"
