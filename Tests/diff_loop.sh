#!/bin/bash
FILES=*.s
for f in $FILES
do
	  echo "Processing $f file..."
	  ./asm $f
	  ./my_asm $f
done

FILES_COR=(*.cor)
FILES_ROR=(*.ror)

echo "cor =  ${FILES_COR[@]}"
echo "ror =  ${FILES_ROR[@]}"

for ((i=0;i<=${#FILES_COR[@]};i++)); do
	 #diff "${FILES_COR[i]}" "${FILES_ROR[i]}"
	if diff ${FILES_COR[i]} ${FILES_ROR[i]} > /dev/null; then
		echo Same
	else
		echo Different
	fi
done

