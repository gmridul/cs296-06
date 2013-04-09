#!/bin/bash


read path
cd $path

file=$(find -type f | wc -l)
dir=$(find -mindepth 1 -type d | wc -l)
echo "No. of files present in this path are ${file}"
echo "No. of directories present in this path are ${dir}"
echo "The list of executables in the path is :-"
find . -executable -type f

