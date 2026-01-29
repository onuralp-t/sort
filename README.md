# SORT
* Sort functions expect a file named `out.bin` file in current directory to have random bytes, those random bytes are interpreted as `int64_t`'s when reading the file.
* run `*.bat` files to compile
* try example command
```ps1
.\bingen.exe --generate 100 ; .\qsort_stdlib.exe
```
## PLATFORM-SPECIFIC
* `bingen.c` calls Windows function `BCryptGenRandom` to generate random numbers and writes them to `out.bin` using C standard library.
* Implement a `int64_t rand_i64(void)` function that generates a random 64 bit integer inside the `bingen.c` to port to other platforms, or just have your own `out.bin` file and skip the generator altogether.