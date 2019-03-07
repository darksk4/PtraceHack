#!/bin/bash
mkdir -p ./build
cd ./build
unzip -P "crackmes.one" ../5b9d312233c5d45fc286ae03.zip
tar xvzf noprelo.tar.gz
mv ./noprelo/noprelo program
rm -rf ./noprelo
cmake .. $1
if [ $1 ]
then
    ninja
else
    make
fi
./execute
