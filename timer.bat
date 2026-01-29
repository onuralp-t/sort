@echo off
set CFLAGS=^
-Wall -Wextra -pedantic ^
-O0 -s

set linking=

@echo on
gcc %CFLAGS% -o timer.exe timer.c %linking% && .\timer.exe
@echo off
rem gcc %CFLAGS% -o timer.exe timer.c %linking% && .\timer.exe && del .\timer.exe
