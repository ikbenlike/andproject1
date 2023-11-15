#!/bin/bash

for i in {1..26}
do
	ans=$(cat "$i.ans")
	out=$(cat "$i.in" | ./project1)
	if [ "$ans" = "$out" ]; then
		echo "Test $i successful"
	else
		echo "Test $i failed"
	fi
done
