#!/bin/bash

GCC="gcc-9 -fno-asynchronous-unwind-tables -fno-exceptions -fno-pic -no-pie -fno-stack-protector -mmanual-endbr -mpreferred-stack-boundary=2 -m32 -O0"

if [ $# -ne 1 ]; then
  echo "Usage: $0 <test_file>"
  exit 1
fi

## Set working directory
cd $(dirname "$0")

if [ ! -f $1 ]; then
  echo "File $1 does not exist"
  exit 1
fi

sed -i '1i #include <stdio.h>' $1
$GCC -Werror $1 -o /dev/null
status=$?
sed -i '1d' $1

if [ $status -ne 0 ]; then
  echo "Invalid testcase: GCC Compilation failed"
  exit 1
fi

./phase $1
