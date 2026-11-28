@echo off
g++ -std=c++11 -Wall -Wextra -Wpedantic main.cpp Tree.cpp LinkedList.cpp QuanLyThanhVien.cpp FamilyRelations.cpp -o gia_pha.exe
if errorlevel 1 exit /b 1
gia_pha.exe
