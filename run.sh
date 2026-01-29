#!/bin/sh

if [ $# -eq 0 ]; then
    echo "Укажите имя файла из папки example"
    echo "Пример: $0 ex4.txt"
    exit 1
fi

mkdir -p build
cd build

cmake .. && make

./test_task "../example/$1"