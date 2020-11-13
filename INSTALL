#! /usr/bin/env bash
# run with sudo if possible
# otherwise, issue with 'make install'

GENERATOR="Unix Makefiles"

mkdir modules/glad/build
cd modules/glad/build
cmake .. -G "$GENERATOR"
make -j12

cp -R include/* ../../../sources
cp src/glad.c ../../../sources/glad/glad.c

cd ../../../

mkdir modules/opencv/build
cd modules/opencv/build
cmake .. -G "$GENERATOR"
make -j12
make install

cd ../../../

mkdir -p build
cd build
cmake .. -G "$GENERATOR"
