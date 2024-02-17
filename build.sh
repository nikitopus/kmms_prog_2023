#!/bin/bash

# Установка локали в UTF-8
export LC_ALL=C.UTF-8

# Тип сборки и суффикс в названии каталога сборки
BUILD_TYPE=Ninja
BUILD_SUFFIX=ninja

BUILD_FOLDER=build_$BUILD_SUFFIX
SOURCE_FOLDER=projects

# Создание каталога сборки, если его нет
mkdir -p $BUILD_FOLDER

# Переход в каталог сборки
cd $BUILD_FOLDER

# Генерация проекта с использованием CMake
cmake -G $BUILD_TYPE ../$SOURCE_FOLDER
# Сборка проекта
cmake --build .

# Задание массива
declare -A arr
arr[0,file]=run_bubble.sh
arr[1,file]=run_bubble_sort_mf.sh
arr[2,file]=run_refactoring.sh
arr[3,file]=run_smartSort.sh
arr[0,folder]=npushkarev_bubble
arr[1,folder]=bubble_sort_mf
arr[2,folder]=refactoring
arr[3,folder]=smartSort

# Копирование файлов в цикле
for i in {0..3}; do
    cp ../$SOURCE_FOLDER/${arr[$i,folder]}/${arr[$i,file]} ./${arr[$i,folder]}
done
