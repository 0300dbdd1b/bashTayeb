if [ $# -eq 1 ]; then
	mode="dernier"
	path="$1"
elif [ "$1" != "-a" ]  && [ "$1" != "-p" ]; then
	echo "Argument Invalide"
	exit 1
else #./findbackup -a 20250505220101 monfichier
	mode=$1
	date_critere=$2
	path=$3
fi


backup_dir="$HOME/.backup"
real_path=$(realpath $path)

if ! echo "$real_path" | grep -q $HOME; then
	echo "doit etre dans le HOME"
	exit 1
fi

relative_path=${real_path#"$HOME"/}

if [ ! -f $real_path ]; then
	echo "$real_path n'est pas un fichier"
	exit 1
fi

cd $backup_dir

dirs=()
case $mode in
	dernier) dirs=($(ls -1 | sort -r)) ;;
	-a)
		dirs=($(ls -1 | sort -r | awk -v date="$date_critere" '$1 < date'))
		;;
	-p)
		dirs=($(ls -1 | sort -r | awk -v date="$date_critere" '$1 > date'))
		;;
esac

for dir in "${dirs[@]}"; do
	candidat="$backup_dir/$dir/$relative_path"
	if [ -f "$candidat" ]; then
		echo $candidat
		exit 0
	fi
done

echo "Rien trouve"
exit 1
