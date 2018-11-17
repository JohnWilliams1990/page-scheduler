#!/bin/bash
#  John Williams
#  105201054
#  Date: Sat. Nov. 17, 2018
#  Program: run.sh

count=(128 256 512 1024)

for i in ${count[@]} ; do 

  echo $i 
  ./pageSwap $i pg-reference.txt stuff
done 




