#!/bin/bash

if [ $# -ne 1 ]; then
  echo "Usage: $0 <roll number>"
  exit 1
fi

## Set working directory
cd $(dirname "$0")

./reset.sh
./setup.sh
./gen.sh $1
python eval.py $1
