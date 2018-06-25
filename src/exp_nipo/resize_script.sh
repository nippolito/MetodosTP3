CONTADOR=0
SIZE_IMAGE=32
P=$(ls *.png);
for filename in $P ; do
	SUFIX=$(echo $filename |cut -d'.' -f 1)
	convert $filename -resize $SIZE_IMAGEx$SIZE_IMAGE resize_$SUFIX.png
	
done
