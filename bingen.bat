@echo off
set CFLAGS=^
-Wall -Wextra -pedantic ^
-O3 -s -std=c23

set linking=-lbcrypt

@echo on
gcc %CFLAGS% -o bingen.exe bingen.c %linking% && .\bingen.exe
@echo off
rem gcc %CFLAGS% -o bingen.exe bingen.c %linking% && .\bingen.exe && del .\bingen.exe
