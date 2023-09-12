#!/bin/bash

i=0
j=10
while [ $i -lt 1000 ]; do
	cmd="./philo 5 190 60 60 4| grep eating | wc -l"
	j=$(eval $cmd)
	echo "test$(expr $i + 1):$j"
	if [ $j -lt 20 ]; then
		echo "error"
		break
	fi
	i=$[$i+1]
done
if [ $i -eq 100 ]; then
	echo "good"
fi
