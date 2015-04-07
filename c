#!/bin/bash
mkdir -p build/Debug/CLang-Linux-x86
rm -f "build/Debug/CLang-Linux-x86/csvreader.o.d"
clang++    -c -g   -stdlib=libc++ -std=c++11 -MMD -MP -MF "build/Debug/CLang-Linux-x86/csvreader.o.d" -o build/Debug/CLang-Linux-x86/csvreader.o csvreader.cpp
mkdir -p build/Debug/CLang-Linux-x86
rm -f "build/Debug/CLang-Linux-x86/main.o.d"
clang++    -c -g   -std=c++11 -stdlib=libc++ -MMD -MP -MF "build/Debug/CLang-Linux-x86/main.o.d" -o build/Debug/CLang-Linux-x86/main.o main.cpp
mkdir -p dist/Debug/CLang-Linux-x86
clang++     -o dist/Debug/CLang-Linux-x86/csv-extractor build/Debug/CLang-Linux-x86/csvreader.o build/Debug/CLang-Linux-x86/main.o -lmysqlcppconn -lmysqlcppconn-static -lc++
