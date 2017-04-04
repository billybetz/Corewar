#!/bin/zsh

if [ "$#" -eq 0 ]; then
	echo "no arguments"
	exit 1
fi

NAME=$1
ASM=asm
ASMO=tests/asm_or
COR=$(echo $NAME | sed 's/\.s/\.cor/g')
ASMONAME="${COR}_or"

echo "name" $NAME
echo "asm" $ASM
echo "asmo" $ASMO
echo "cor" $COR
echo "asmoname" $ASMONAME

make
./$ASMO $NAME
mv $COR $ASMONAME
./$ASM $NAME
clear
hexdump $NAME
echo "diff:"
diff -u $COR $ASMONAME 
#rm $COR
#rm $ASMONAME
