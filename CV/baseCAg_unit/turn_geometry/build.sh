#!/bin/bash
g++ geometryTurn.cpp -o geometryTurn `pkg-config --cflags --libs opencv` 
echo "build finish, excution application now!"
