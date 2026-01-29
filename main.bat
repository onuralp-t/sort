@echo off
set CFLAGS=^
-Wall -Wextra -pedantic ^
-O3 -s -std=c23

set linking=-lbcrypt

@echo on
gcc %CFLAGS% -o main.exe main.c %linking% && .\main.exe
@echo off
rem gcc %CFLAGS% -o main.exe main.c %linking% && .\main.exe && del .\main.exe
