#!/bin/sh

if [ "$#" != 2 ]; then
	echo "Error : need two .s files"
	exit 1
fi

NAME1=$1
NAME2=$2

if ! [ -e $NAME1 ]; then
	echo "Error : the file \"$NAME1\" doesn't exist"
	exit 1
fi

if ! [ -e $NAME2 ]; then
	echo "Error : the file \"$NAME2\" doesn't exist"
	exit 1
fi

ASM=assembleur/asm
ASM_OR=~/Downloads/corewar/ressources/asm
EXEC_COR_OR=~/Downloads/corewar/corewar
EXEC_COR=vm/corewar
COR1=$(echo $NAME1 | sed 's/\.s/\.cor/g')
COR2=$(echo $NAME2 | sed 's/\.s/\.cor/g')

rm $COR1 $COR2

make
clear
echo "\n.cor CREATING ."
sleep 0.7
clear
echo "\n.cor CREATING .."
sleep 0.7
clear
echo "\n.cor CREATING ..."
sleep 0.7

$ASM_OR $NAME1
$ASM_OR $NAME2

#./$ASM $NAME1
#./$ASM $NAME2

if ! [ -e $COR1 ]; then
	echo "Error : could not create $COR1 file"
	exit 1
fi

if ! [ -e $COR2 ]; then
	echo "Error : could not create $COR2 file"
	exit 1
fi

clear
echo "\n.cor created !"
sleep 1

clear
echo "\nEXECUTE COREWAR WITH $COR1 and $COR2 ."
sleep 0.7
clear
echo "\nEXECUTE COREWAR WITH $COR1 and $COR2 .."
sleep 0.7
clear
echo "\nEXECUTE COREWAR WITH $COR1 and $COR2 ..."
sleep 0.7
## ./$EXEC_COR -n $COR1 $COR2
$EXEC_COR_OR -n $COR1 $COR2




