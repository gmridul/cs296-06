#!/bin/bash

cd ../data
rm -f lab05_g06_data.csv
touch lab05_g06_data.csv
cd ../mybins
for rerun in {1..100}
do
	for iter in {1..100}
	do
		printf $rerun,$iter, >> ../data/lab05_g06_data.csv
		./cs296_exe_06 $iter | awk '{
			if(NF==7 && $4=="loop")
				{printf "%f",$6;}
			else if(NF==7)
				{printf "%f,",$6;}
			else if(NF==8)
				{printf "%f,",$7;}
		}' >> ../data/lab05_g06_data.csv
	printf "\n" >> ../data/lab05_g06_data.csv
	done
done
