#!/bin/bash

i=0
j=10
while [ $i -lt 100 ]; do
	cmd="./philo 5 800 200 200 4| grep eating | wc -l"
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
