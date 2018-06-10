CONTADOR=0
P=$(ls *.png);
for filename in $P ; do
	SUFIX=$(echo $filename |cut -d'.' -f 1)
	convert $filename $SUFIX'.ppm'
	rm $filename
done