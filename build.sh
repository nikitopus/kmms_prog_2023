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
arr[0,folder]=npushkarev_bubble
arr[1,folder]=bubble_sort_mf

# Копирование файлов в цикле
for i in {0..1}; do
    cp ../$SOURCE_FOLDER/${arr[$i,folder]}/${arr[$i,file]} ./${arr[$i,folder]}
done
