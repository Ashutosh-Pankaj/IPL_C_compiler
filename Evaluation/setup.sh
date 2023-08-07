#!/bin/bash

GCC="gcc-9 -fno-asynchronous-unwind-tables -fno-exceptions -fno-pic -no-pie -fno-stack-protector -mmanual-endbr -mpreferred-stack-boundary=2 -m32 -O0"
## Set working directory
cd $(dirname "$0")

## Make required directories
mkdir -p ./asm/ ./output/ ./stdout/

for testpath in ./tests/*.c; do
    testcase=$(basename $testpath .c)
    sed -i '1i #include <stdio.h>' ./tests/$testcase.c
    $GCC -Werror -S ./tests/$testcase.c -o ./asm/$testcase.s
    $GCC ./asm/$testcase.s -o ./output/$testcase.o
    ./output/$testcase.o > ./stdout/$testcase.txt
    sed -i '1d' ./tests/$testcase.c
done
