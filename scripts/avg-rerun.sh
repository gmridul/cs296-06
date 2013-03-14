#!/bin/bash

cd ../data
rm -f  avg_rerun.csv
touch avg_rerun.csv

awk '
BEGIN {
	FS=","
	OFS=",";
}
{	
		for(i=3;i<8;i++) {
			avg[$2,i] += $i
		}
		if($1==100 && $2==100) {
			for(k=1;k<=100;k++) {
				printf "%d,",k
				for(j=3;j<8;j++) {
					avg[k,j] = avg[k,j]/100
					printf "%f",avg[k,j]
					if(j<7) {printf ","}
				}
				printf "\n"
			}
		}
}' lab05_g06_data.csv >> avg_rerun.csv
