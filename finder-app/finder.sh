#!/bin/bash
filesdir=$1
searchstr=$2

if [ $# != 2 ]
then
	echo "Finder requires 2 argument"
	exit 1
fi

if  [ ! -d $filesdir ]
then
	echo "$filesdir Not a directory"
	exit 1
fi

count_file=$(find $filesdir -maxdepth 1 -type f | wc -l)
count_lines=$(grep -r $searchstr $filesdir | wc -l)
echo "The number of files are $count_file and the number of matching lines are $count_lines"

exit 0
