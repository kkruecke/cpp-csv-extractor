#!/bin/bash
mkdir -p build/Debug/GNU-Linux-x86
rm -f "build/Debug/GNU-Linux-x86/csvreader.o.d"
clang++    -c -g -I/usr/include/mysql++ -I/usr/include/mysql -stdlib=libc++ -std=c++11 -MMD -MP -MF "build/Debug/GNU-Linux-x86/csvreader.o.d" -o build/Debug/GNU-Linux-x86/csvreader.o csvreader.cpp
mkdir -p build/Debug/GNU-Linux-x86
rm -f "build/Debug/GNU-Linux-x86/main.o.d"
clang++    -c -g -I/usr/include/mysql++ -I/usr/include/mysql -std=c++11 -stdlib=libc++ -MMD -MP -MF "build/Debug/GNU-Linux-x86/main.o.d" -o build/Debug/GNU-Linux-x86/main.o main.cpp
mkdir -p dist/Debug/GNU-Linux-x86
clang++     -o dist/Debug/GNU-Linux-x86/csv-extractor build/Debug/GNU-Linux-x86/csvreader.o build/Debug/GNU-Linux-x86/main.o -lmysqlcppconn -lmysqlcppconn-static -lc++
