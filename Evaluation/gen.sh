#!/bin/bash

GCC="gcc-9 -fno-asynchronous-unwind-tables -fno-exceptions -fno-pic -no-pie -fno-stack-protector -mmanual-endbr -mpreferred-stack-boundary=2 -m32 -O0"
if [ $# -ne 1 ]; then
  echo "Usage: $0 <roll number>"
  exit 1
fi

## Set working directory
cd $(dirname "$0")

## Full path to the submission folder
SUBMISSION_FOLDER=~/final-submissions/

## Make required directories
mkdir -p ./input
mkdir -p ./dump/$1
mkdir -p ./diff/$1
mkdir -p ./exec
mkdir -p ./asm/$1
mkdir -p ./output/$1
mkdir -p ./stdout/$1

## Untar file
cd ./input
if [ ! -f $SUBMISSION_FOLDER/$1.tar.gz ]; then
    echo "Error: Submission not found" &> ../dump/$1/error.dump
    exit
fi
tar -zxf "$SUBMISSION_FOLDER/$1.tar.gz"

## Find code folder
if [ -d $1 ]; then
    code=$1
else
    echo "Error: Untarring failed" &> ../dump/$1/error.dump
    exit
fi

## Compile
cd $code
grep -rIL . > ../../dump/$1/binaries.dump
make all > ../../dump/$1/make_all.dump 2>&1

## Save the executable
if [ ! -f "iplC" ]; then
    echo "Error: iplC not found" &> ../../dump/$1/error.dump
    exit
fi
cp iplC ../../exec/$1-iplC

## Test
cd ../..
chmod 775 ./exec/$1-iplC
for testpath in ./tests/*.c; do
    testcase=$(basename $testpath .c)
    timeout 1s ./exec/$1-iplC ./tests/$testcase.c > ./asm/$1/$testcase.s 2> /dev/null
    if [ $? -ne 0 ]; then
        echo "./tests/$testcase.c compile TLE" > ./diff/$1/$testcase.diff
        continue
    fi
    $GCC ./asm/$1/$testcase.s -o ./output/$1/$testcase.o > /dev/null 2> /dev/null
    timeout 1s ./output/$1/$testcase.o > ./stdout/$1/$testcase.txt 2> /dev/null
    if [ $? -ne 0 ]; then
        echo "./tests/$testcase.c exeucte TLE" > ./diff/$1/$testcase.diff
        continue
    fi
    diff ./stdout/$1/$testcase.txt ./stdout/$testcase.txt > ./diff/$1/$testcase.diff
done
wc -l ./diff/$1/*.diff > ./dump/$1/diff.dump
