#!/bin/bash

if [ $1 = 2 ] ; then
	op=debug
elif [ $1 = 1 ] ; then
	op=release
fi

rm -f g06_$op\_prof.dat

for (( iter=10; iter<=100; iter+=10 ))
do
	for (( rerun=10; rerun<=100; rerun+=10 ))
	do
		echo -e "profile for iteration no. ${iter} and rerun no. ${rerun} ::\n" >> g06_$op\_prof.dat
		../bin/cs296_base_analysis $iter >> /dev/null
		gprof -p -b ../bin/cs296_base_analysis gmon.out >> g06_$op\_prof.dat
		echo -e "*************************************************************\n" >> g06_$op\_prof.dat
	done
done
