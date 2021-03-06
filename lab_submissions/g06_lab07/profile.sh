#!/bin/bash

if [ $1 = 2 ] ; then
	op=debug
elif [ $1 = 1 ] ; then
	op=release
fi

rm -f g06_$op\_prof.dat

for (( iter=1000; iter<=10000; iter+=1000 ))
do
	for (( rerun=1000; rerun<=10000; rerun+=1000 ))
	do
		echo -e "profile for iteration no. ${iter} and rerun no. ${rerun} ::\n" >> g06_$op\_prof.dat
		mybins/cs296_exe_06 $iter >> /dev/null
		gprof -p -b mybins/cs296_exe_06 gmon.out >> g06_$op\_prof.dat
		echo -e "*************************************************************\n" >> g06_$op\_prof.dat
	done
done
