#!/bin/bash

cmake -B build/Release -DCMAKE_BUILD_TYPE:STRING=Release -DCMAKE_CXX_FLAGS_INIT:STRING= -DCMAKE_C_COMPILER:FILEPATH=/usr/bin/clang-17 -DQT_QMAKE_EXECUTABLE:FILEPATH=${HOME}/Qt/6.8.0/gcc_64/bin/qmake -DCMAKE_GENERATOR:STRING=Ninja -DCMAKE_PREFIX_PATH:PATH=${HOME}/Qt/6.8.0/gcc_64 -DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/clang++-17 in build/Release.

cmake --build build/Release --target all -j $(nproc --all)
