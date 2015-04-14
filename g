#!/bin/bash
rm -f -r build/Debug
rm -f dist/Debug/GNU-Linux-x86/csv-extractor
mkdir -p build/Debug/GNU-Linux-x86
rm -f "build/Debug/GNU-Linux-x86/csvparser.o.d"
g++    -c -g -std=c++11 -MMD -MP -MF "build/Debug/GNU-Linux-x86/csvparser.o.d" -o build/Debug/GNU-Linux-x86/csvparser.o csvparser.cpp
mkdir -p build/Debug/GNU-Linux-x86
rm -f "build/Debug/GNU-Linux-x86/main.o.d"
g++    -c -g -std=c++11 -MMD -MP -MF "build/Debug/GNU-Linux-x86/main.o.d" -o build/Debug/GNU-Linux-x86/main.o main.cpp
mkdir -p dist/Debug/GNU-Linux-x86
g++     -o dist/Debug/GNU-Linux-x86/csv-extractor build/Debug/GNU-Linux-x86/csvparser.o build/Debug/GNU-Linux-x86/main.o -lmysqlcppconn -lmysqlcppconn-static 
