#!/bin/bash
#**
#******************************************************************************
#* @file    /cli_examples/bash/bash_args.sh
#* @author  Adrian Wojcik
#* @version V1.0
#* @date    14-Mar-2020
#* @brief   Raspberry Pi CLI apps example: bash with getopt
#******************************************************************************

nonoptionargs=()
flagstate=("RESET" "SET")
aflag=0
bflag=0
cvalue=""
echo "Bash CLI example"
# standard while/case procedure for 'getopt' function 
while [ $# -gt 0 ]; do
	while getopts ":abc:" opt; do
		case $opt in
			a) 
				aflag=1 ;;
			b) 
				bflag=1 ;;
			c) 
				cvalue=$OPTARG ;; 
			\?) 
				echo "option '-$OPTARG not recognized'"
				exit 1 ;;
			: )
				echo "option '-$OPTARG' requires argument" 
				exit 1 ;;
		esac
	done
	shift $((OPTIND-1))

	while [ $# -gt 0 ] && ! [[ "$1" =~ ^- ]]; do
		nonoptionargs=("${nonoptionargs[@]}" "$1")
		shift
	done
done

# Printing results 
echo "a (flag) = ${flagstate[$aflag]}"
echo "b (flag) = ${flagstate[$bflag]}"
echo "c (value) = $cvalue"
index=1
if [ ${#nonoptionargs[@]} -gt 0 ]; then
    for noa in "${nonoptionargs[@]}"
	do
		echo "Non-option argument #$index: $noa"
		index=$((index+1))
	done
fi
