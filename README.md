# ручная сборка
mkdir -p build && cd build
cmake .. && make

# запуск
./test_task ../example/example.txt

# скрипт для сборки
chmod += run.sh
./run.sh имя_файла_из_example