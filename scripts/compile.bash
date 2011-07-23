#
# Copyright (c) Patryk Jaworski
# 
FLAGS="-rdynamic";
if [ "$1" = "--static" ]; then
	#FLAGS="$FLAGS -static-libstdc++ -static-libgcc";
	FLAGS="$FLAGS -static";
fi;
echo "[I] Creating modules list...";
./scripts/create-modules-list.bash;
echo "[I] Compiling CMS...";
cd src/;
find . -name "*.cpp" | while read F; do
	OBJ="${F/\.cpp/.o}"
	if [ $F -nt $OBJ ]; then
		echo " [C] Compiling $F"; g++ -c "$F" -o "$OBJ";
	else
		echo " [C] Skipping $F";
	fi;
	if [ $? != 0 ]; then
		echo " [E] Error while compiling \"$F\"...";
		exit 1;
	fi;
done;

rm objs > /dev/null 2>&1;
find . -name "*.o" | while read F; do echo "$F" >> objs; done;

echo "[I] Linking files...";

g++ $FLAGS -o ../index.cgi `cat objs | xargs`;
rm objs > /dev/null 2>&1;

echo "[I] Binary size: $(du -h ../index.cgi | cut -f 1)";
