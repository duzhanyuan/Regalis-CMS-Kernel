cd src/
OUT="modules/all.hpp"
OUT2="modules/register.hpp"
echo "#ifndef _ALL_MODULES" > $OUT;
echo "#define _ALL_MODULES" >> $OUT;
echo -n "" > $OUT2;
for F in modules/*; do
	M=$(basename "$F");
	if [ -d "$F" -a -f "$F/main.cpp" -a -f "$F/main.hpp" ]; then
		echo " [M] Found module $M";
		name="Module`echo ${M:0:1} | tr '[:lower:]' '[:upper:]'`${M:1}";
		echo "#include \"$M/main.hpp\"" >> $OUT;
		echo "KernelModule* $M = new $name;" >> $OUT2;
		echo "modules->add(\"$M\", $M);" >> $OUT2;
	fi;
done;
echo "#endif" >> $OUT;
