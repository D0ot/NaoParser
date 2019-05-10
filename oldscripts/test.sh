#!/bin/bash

#compile and run simple unittest 

g++ -g -Wall -std=c++11 unittest.cpp sexpresso.cpp naometadata.cpp -o unittest
./unittest
