#!/bin/bash

cd ../mybins

for i in {1..100}
do
	for j in {1..100}
	do
		./cs296_exe_06 $i > ../data/out-$i-$j.txt
	done
done
