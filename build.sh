#!/bin/bash

# Вид сборки / суффикс в названии каталога сборки
#
# "Ninja" / "ninja"
# "Visual Studio 17 2022" / "visual_studio"
#
BUILD_TYPE=Ninja
BUILD_SUFFIX=ninja

export BUILD_FOLDER=build_$BUILD_SUFFIX
export SOURCE_FOLDER=projects

mkdir -p $BUILD_FOLDER
cd $BUILD_FOLDER

cmake -G $BUILD_TYPE ../$SOURCE_FOLDER
cmake --build .

cp ../$SOURCE_FOLDER/npushkarev_bubble/run_bubble.sh ./npushkarev_bubble
