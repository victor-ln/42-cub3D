#!/bin/bash

program="./cub3D"
dir=" ./maps/failure/"
file="map_"
tests=11
i=0
extension=""
logs=("file extension" \
"without a player" \
"invalid character" \
"not surrounded" \
"more than a player" \
"double color identifier" \
"invalid color identifier" \
"number of arguments in color element" \
"number of arguments in color element" \
"identifier argument" \
"invalid RGB scale" \
"doubled texture identifier")

while [ $i -le $tests ]
do
	if [ $i -ge 1 ]; then
		extension=".cub"
	fi
	result="`$program $dir$file$i$extension 2>&1 >/dev/null | grep -c Error`"
	echo Testing ${logs[$i]}
	if [ $result == 1 ]; then
		echo -e "\e[1;32mOK\e[0m"
	else
		echo -e "\e[1;31mKO\e[0m"
	fi
	((i++))
done
