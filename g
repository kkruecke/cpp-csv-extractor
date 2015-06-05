#!/bin/bash
rm -f -r build/Debug
rm -f dist/Debug/GNU-Linux-x86/cpp-csv-extractor
mkdir -p build/Debug/GNU-Linux-x86
rm -f "build/Debug/GNU-Linux-x86/fix-text.o.d"
g++    -c -g -std=c++11 -MMD -MP -MF "build/Debug/GNU-Linux-x86/fix-text.o.d" -o build/Debug/GNU-Linux-x86/fix-text.o file-regex-parser.cpp
rm -f "build/Debug/GNU-Linux-x86/file-regex-parser.o.d"
g++    -c -g -std=c++11 -MMD -MP -MF "build/Debug/GNU-Linux-x86/file-regex-parser.o.d" -o build/Debug/GNU-Linux-x86/file-regex-parser.o file-regex-parser.cpp
rm -f "build/Debug/GNU-Linux-x86/petition-parser.o.d"
g++    -c -g -std=c++11 -MMD -MP -MF "build/Debug/GNU-Linux-x86/petition-parser.o.d" -o build/Debug/GNU-Linux-x86/petition-parser.o petition-parser.cpp
rm -f dist/Debug/GNU-Linux-x86/db_credentials
rm -f "build/Debug/GNU-Linux-x86/db_credentials.o.d"
g++    -c -g -std=c++11 -MMD -MP -MF "build/Debug/GNU-Linux-x86/petition-parser.o.d" -o build/Debug/GNU-Linux-x86/db_credentials.o db_credentials.cpp
rm -f "build/Debug/GNU-Linux-x86/main.o.d"
g++    -c -g -std=c++11 -MMD -MP -MF "build/Debug/GNU-Linux-x86/main.o.d" -o build/Debug/GNU-Linux-x86/main.o main.cpp
g++     -o dist/Debug/GNU-Linux-x86/cpp-csv-extractor  build/Debug/GNU-Linux-x86/db_credentials.o  build/Debug/GNU-Linux-x86/file-regex-parser.o build/Debug/GNU-Linux-x86/petition-parser.o build/Debug/GNU-Linux-x86/fix-text.o  build/Debug/GNU-Linux-x86/main.o -lmysqlcppconn -lmysqlcppconn-static 
