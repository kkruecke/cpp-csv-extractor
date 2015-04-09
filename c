#!/bin/bash
mkdir -p build/Debug/CLang-Linux-x86
mkdir -p build/Debug/CLang-Linux-x86
rm -f "build/Debug/CLang-Linux-x86/main.o.d"
clang++    -c -g   -std=c++11 -stdlib=libc++ -MMD -MP -MF "build/Debug/CLang-Linux-x86/main.o.d" -o build/Debug/CLang-Linux-x86/main.o main.cpp
mkdir -p dist/Debug/CLang-Linux-x86
clang++  -stdlib=libc++   -o dist/Debug/CLang-Linux-x86/csv-extractor build/Debug/CLang-Linux-x86/main.o -lc++
