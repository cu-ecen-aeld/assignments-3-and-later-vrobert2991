#! /bin/bash

if [ $# != 2 ]
then
	echo "Writer requires 2 arguments"
	exit 1
fi

writefile=$1
writestr=$2
folder=$(dirname "$writefile")
mkdir -p "$folder"
echo "$writestr" > "$writefile"

exit 0
