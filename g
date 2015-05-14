#!/bin/bash
rm -f -r build/Debug
rm -f dist/Debug/GNU-Linux-x86/cpp-csv-extractor
mkdir -p build/Debug/GNU-Linux-x86
rm -f "build/Debug/GNU-Linux-x86/petition-parser.o.d"
g++    -c -g -std=c++11 -MMD -MP -MF "build/Debug/GNU-Linux-x86/petition-parser.o.d" -o build/Debug/GNU-Linux-x86/petition-parser.o petition-parser.cpp
rm -f dist/Debug/GNU-Linux-x86/db_credentials
mkdir -p build/Debug/GNU-Linux-x86
rm -f "build/Debug/GNU-Linux-x86/db_credentials.o.d"
g++    -c -g -std=c++11 -MMD -MP -MF "build/Debug/GNU-Linux-x86/petition-parser.o.d" -o build/Debug/GNU-Linux-x86/db_credentials.o db_credentials.cpp
mkdir -p build/Debug/GNU-Linux-x86
rm -f "build/Debug/GNU-Linux-x86/main.o.d"
g++    -c -g -std=c++11 -MMD -MP -MF "build/Debug/GNU-Linux-x86/main.o.d" -o build/Debug/GNU-Linux-x86/main.o main.cpp
mkdir -p dist/Debug/GNU-Linux-x86
g++     -o dist/Debug/GNU-Linux-x86/cpp-csv-extractor  build/Debug/GNU-Linux-x86/db_credentials.o build/Debug/GNU-Linux-x86/petition-parser.o build/Debug/GNU-Linux-x86/main.o -lmysqlcppconn -lmysqlcppconn-static 
