#!/bin/bash

pro_user_array=(
	"GTools"
	"GtoolsM"
	"GtoolsP"
	"GtoolsV"
)

for i in ${pro_user_array[@]}
do
	open ${i}/*.pro 2>/dev/null
done
