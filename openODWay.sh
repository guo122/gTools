#!/bin/bash

pro_user_array=(
	"ODTest"
	"ODWay"
	"ODWayM"
	"ODWayP"
	"ODWayV"
)

for i in ${pro_user_array[@]}
do
	open ${i}/*.pro 2>/dev/null
done
