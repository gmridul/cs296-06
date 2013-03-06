#!/bin/bash

if [ "$1" = "1" ]
then
	tar zcvf src.tar.gz src
elif [ "$1" = "2" ]
then
	gzip src/*
	tar cvf src.tar src
	gunzip src/*
fi
