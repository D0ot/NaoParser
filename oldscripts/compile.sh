#!/bin/bash

#compile main.cpp and run

g++ -g -Wall -std=c++11 main.cpp sexpresso.cpp naometadata.cpp -o test
./test
