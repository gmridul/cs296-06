#!/bin/bash

cd ../bin

for i in {1..100}
do
	for j in {1..100}
	do
		./cs296_base_analysis $i > ../data/out-$i-$j.txt
	done
done
