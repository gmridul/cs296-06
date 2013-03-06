#!/bin/bash

cd ../data
rm -f lab05_g06_data.csv
touch lab05_g06_data.csv
for rerun in {1..100}
do
	for iter in {1..100}
	do
		printf $rerun,$iter, >> lab05_g06_data.csv
		awk '{
			if(NR==2 || NR==3)
				{printf "%f,",$6;}
			else if(NR==7)
				{printf "%f",$6;}
			else if(NR==4||NR==5)
				{printf "%f,",$7;}
		}' out-$iter-$rerun.txt >> lab05_g06_data.csv
	printf "\n" >> lab05_g06_data.csv
	done
done
