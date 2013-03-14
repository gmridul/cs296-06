#!/bin/bash
cd src

if [ "$1" -eq 1 ] ; then
	for file in *.cpp
	do
		mv "$file" "${file/.cpp/.cpp.bak}"
	done
elif [ "$1" -eq 2 ] ; then
	rename 's/.cpp/.cpp.bak/' *.cpp
fi
