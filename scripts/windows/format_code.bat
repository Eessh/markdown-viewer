@echo off

echo Formatting ...

clang-format -i -style=file include\*.h src\*.c main.c

echo Done.

exit