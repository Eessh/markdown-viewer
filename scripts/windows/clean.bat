@echo off

echo Cleaning executables ...
del /q bin\Debug\MarkdownViewer.exe >nul 2>&1
del /q bin\Release\MarkdownViewer.exe >nul 2>&1

echo Cleaning object files ...
del /q obj\Debug\* >nul 2>&1
del /q obj\Release\* >nul 2>&1

echo Cleaning misc files ...
del /q Makefile >nul 2>&1
del /q *.make >nul 2>&1

echo Done.

exit