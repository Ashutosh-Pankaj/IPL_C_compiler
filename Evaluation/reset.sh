#!/bin/bash

## Set working directory
cd $(dirname "$0")

## Clean all directories
rm -rf dump/ exec/ input/ asm/ output/ stdout/ diff/ final.csv
