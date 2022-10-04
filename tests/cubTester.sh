#!/bin/bash

# Mandatory test
make -C ..
program="../cub3D"

# Bonus test
# make -C ../ bonus
# program="../cub3D_bonus"

dir=" ./failure/"
file="map_"
tests=26
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
"doubled texture identifier" \
"zero on right border" \
"zero on right border 2" \
"zero on bottom" \
"map_15 not_surrounded 1" \
"map_16 not_surrounded 2" \
"map_17 not_surrounded 3" \
"map_18 not_surrounded 4" \
"map_19 not_surrounded 5" \
"map_20 not_surrounded 6" \
"map_21 not_surrounded 7" \
"map_22 not_surrounded 8" \
"map_23 not_surrounded 9" \
"map_24 not_surrounded 10" \
"map_25 not_surrounded 11" \
"map_26 not_surrounded 12")

while [ $i -le $tests ]
do
	if [ $i -ge 1 ]; then
		extension=".cub"
	fi
	result="`$program $dir$file$i$extension | grep -c Error`"
	# result="`valgrind --leak-check=full --show-leak-kinds=all $program $dir$file$i$extension`"
	echo Testing ${logs[$i]}
	if [ $result == 1 ]; then
		echo -e "\e[1;32mOK\e[0m"
	else
		echo -e "\e[1;31mKO\e[0m"
	fi
	((i++))
done

