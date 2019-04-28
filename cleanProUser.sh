#!/bin/bash

pro_user_array=(
	"GTools"
	"GtoolsM"
	"GtoolsP"
	"GtoolsV"
	"ODTest"
	"ODWay"
	"ODWayM"
	"ODWayP"
	"ODWayV"
)

for i in ${pro_user_array[@]}
do
	rm ${i}/*.pro.user 2>/dev/null
done
