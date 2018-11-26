#!/bin/bash
#  John Williams
#  105201054
#  Date: Sat. Nov. 17, 2018
#  Program: run.sh

count=(128 256 512 1024)
#count=(2 4 8 16)
file='stuff'
inputFile='pg-reference.txt'
#inputFile='sample.txt'
#inputFile='sample2.txt'
#inputFile='pg-reference.txt'
rm -f $file
for i in ${count[@]} ; do 
  echo $i 
  ./pageSwap $i $inputFile $file
done 

cp stuff ./graph/
./graph/graphing2.py

