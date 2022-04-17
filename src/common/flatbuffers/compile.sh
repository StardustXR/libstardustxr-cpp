#!/bin/sh

cd "${MESON_SOURCE_ROOT}/${MESON_SUBDIR}";
echo "Executing in dir ${PWD}";

echo -e "\nFound flatbuffers schemas:";
find . -name "*.fbs" -type f -printf "%f\n";

echo -e "\nRemoving all old headers:";
rm -v *.hpp;
flatc -c *.fbs --scoped-enums --gen-name-strings --gen-mutable --filename-suffix "" --filename-ext "hpp" &&

echo -e "\nCompiled headers:";
find . -name "*.hpp" -type f -printf "%f\n";
