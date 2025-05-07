if [ $# -ne 1 ]; then
	echo "Must provide only one argument"
	exit 1
fi

#$1 test
timestamp=$(date +%y%m%d%H%M%S)
backup_folder="$HOME/.backup/$timestamp"
real_path=$(realpath $1)
#real_path= /home/somefolder/test

if ! echo $real_path | grep -q $HOME; then
	echo "Not in $HOME directory"
	exit 1
fi

if [ ! -d  $real_path ]; then
	echo "Must provide a directory"
	exit 1
fi

mkdir -p $backup_folder
find $real_path | grep -v "$HOME/.backup" | while read -r FILE;do #Pour tout les fichiers qui ne contiennent pas $HOME/.backup


SRC_PATH="${FILE#HOME/}" #supprimer "$HOME/" de FILE
#somefolder/test
DEST_PATH="$backup_folder/$SRC_PATH"
#$HOME/tayeb/.backup/$timestamp
if [ -d "$FILE" ]; then #Si direcory
	mkdir -p $DEST_PATH
else	#Sinon File if [ -L "$FILE" ]; then #si lien symbolique
		cp -p "$FILE" $DEST_PATH
	else #sinon regular file
		cp "$FILE" $DEST_PATH
	fi
fi


done

find $backup_folder -type f -exec chmod 400 {} +;
find $backup_folder -type d -exec chmod 500 {} +;
exit 0
