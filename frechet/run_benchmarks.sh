#!/bin/bash
FILE="data.csv"
if [ -e "$FILE" ]; then
	rm $FILE
else
	echo "Se creara $FILE"
fi
echo "time, filename" >> $FILE
#benchmarkDir="test_files"
benchmarkDir="benchmarks"
outputDir="outputs"
if [ -d "$outputDir" ]; then
rm -r $outputDir
fi
mkdir -p $outputDir

for i in $( ls -1 $benchmarkDir | grep .in | sed -e 's/\..*$//') ;
	do
		echo $i
		time=$(/usr/bin/time -f'%e' 2>&1 ./src/frechet $(pwd)/$benchmarkDir/$i.in $(pwd)/$outputDir/$i.out > /dev/null)
		echo "$time, $i" >> $FILE
    done
  echo "" >> $FILE

