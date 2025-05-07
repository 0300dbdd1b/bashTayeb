
if [ $# -ne 1 ]; then
	echo "Must provide only one argument"
	exit 1
fi

timestamp=$(date +%y%m%d%H%M%S)
backup_folder="$HOME/.backup/$timestamp"
real_path=$(realpath $1)

if ! echo $real_path | grep -q $HOME; then
	echo "Not in $HOME directory"
	exit 1
fi

if [ ! -d  $real_path ]; then
	echo "Must provide a directory"
	exit 1
fi

mkdir -p $backup_folder
cp -R $real_path $backup_folder
find $backup_folder -type f -exec chmod 400 {} +;
find $backup_folder -type d -exec chmod 500 {} +;
exit 0
