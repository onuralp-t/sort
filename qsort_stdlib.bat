@echo off
set CFLAGS=^
-Wall -Wextra -pedantic ^
-Og -ggdb3 -std=c23

set linking=

@echo on
gcc %CFLAGS% -o qsort_stdlib.exe qsort_stdlib.c %linking% && .\qsort_stdlib.exe
@echo off
rem gcc %CFLAGS% -o qsort_stdlib.exe qsort_stdlib.c %linking% && .\qsort_stdlib.exe && del .\qsort_stdlib.exe
