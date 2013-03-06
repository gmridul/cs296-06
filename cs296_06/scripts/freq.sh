#!/bin/bash

cd ../data
rm -f freq.csv
touch freq.csv
awk '
BEGIN {
	FS=","
	OFS=","
}
{
	if($2==24) {
		freq[$3]++
	}
	if($1==100) {
		for(i in freq) {
			printf "%s,%d\n",i,freq[i]
		}
	}
}' lab05_g06_data.csv >> freq.csv

