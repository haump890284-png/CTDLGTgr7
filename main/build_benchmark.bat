@echo off
g++ -std=c++11 -Wall -Wextra -Wpedantic benchmark.cpp Tree.cpp LinkedList.cpp -o benchmark.exe
if errorlevel 1 exit /b 1
benchmark.exe
