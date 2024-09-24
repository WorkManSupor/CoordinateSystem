#!/bin/bash
g++ geometrySymmetry.cpp -o geometrySymmetry `pkg-config --cflags --libs opencv` 
echo "build finish, excution application now!"
