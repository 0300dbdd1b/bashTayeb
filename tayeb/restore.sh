scriptpath=$(realpath $0)
scriptdir=$(dirname $scriptpath)

#check preliminaires
if [ $# -eq 1 ]; then	#si le nombre d'argument = 1 alors on lance findbackupv1 avec le path ($1)
	result=$("$scriptdir"/findbackupv1.sh "$1")
elif [ $# -neq 3 ]; then	#si le nombre d'argument est pas 3 alors exit 1
	echo "Nombre d'argument invalide"
	exit 1
elif [ "$1" != "-a" ]  && [ "$1" != "-p" ]; then #si le premier argument est pas -a ni -p alors exit
	echo "Argument Invalide"
	exit 1
else
	result=$("$scriptdir"/findbackupv1.sh $1 $2 $3) #le nombre d'arg = 3 et $1 = -a ou -p, on lance findbackup avec le mode la date et le path
fi

if [ $? -ne 0 ]; then	#si findbackup exit 1 (erreur), alors on exit aussi
	echo "Aucune version a restaurer -- Finbackup error"
	exit 1
fi

#si on a pas exit (findbackup a trouve un fichier backup)
if [ -L $result ]; then #si lien symbolique on copy
	cp -R $result $pwd
else
	cp $result $pwd
fi
exit 0
