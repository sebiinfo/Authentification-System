#!/bin/bash
for i in {1..15}
do
  mkdir "$i" 
done

for i in {1..9}
do
  echo $i
  mv subject0$i.* "$i"
done

for i in {10..15}
do
  echo $i
  mv subject$i.* "$i"
done

for FILE in *; do
  a=1; 
  for j in "$FILE"/*; do
    convert "$j" "$FILE/$a.png";
    ((a=a+1))
  done;
done;
