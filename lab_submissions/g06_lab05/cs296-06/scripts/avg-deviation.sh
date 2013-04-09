#!/bin/bash

cd ../data
rm -f  avg_iteration.csv
touch avg_iteration.csv

awk '
BEGIN {
	FS=","
	OFS=",";
}
{	
		for(i=3;i<8;i++) {
			avg["a",$1,i] += $i
			avg["d",$1,i] += $i*$i
		}
		if($1==100 && $2==100) {
			for(k=1;k<=100;k++) {
				printf "%d,",k
				for(j=3;j<8;j++) {
					avg["a",k,j] = avg["a",k,j]/100
					avg["d",k,j] = sqrt(avg["d",k,j]/100 - avg["a",k,j]*avg["a",k,j])
					printf "%f,%f",avg["a",k,j],avg["d",k,j]
					if(j<7) {printf ","}
				}
				printf "\n"
			}
		}
}' lab05_g06_data.csv >> avg_deviation.csv
