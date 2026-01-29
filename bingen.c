
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define BCRYPT_USE_SYSTEM_PREFERRED_RNG 2

#define WINAPI_ __attribute((dllimport,stdcall))
WINAPI_ int32_t BCryptGenRandom(void* z0, uint8_t* buf, uint32_t bufsize, uint32_t flags);

int64_t rand_i64(void)
{
    int64_t val = 0;
    BCryptGenRandom(NULL, (uint8_t*)&val, sizeof(val), BCRYPT_USE_SYSTEM_PREFERRED_RNG);
    return val;
}

void rand_i64_write(const char* dst_path, int64_t buffer_count)
{
    int64_t *array = (int64_t*)malloc(sizeof(int64_t) * buffer_count);

    for (int64_t i = 0; i < buffer_count; ++i)
    {
        array[i] = rand_i64();
    }

    FILE *f = fopen(dst_path, "wb");
    fwrite(array, sizeof(int64_t), buffer_count, f);
    fclose(f);
}

int main(int argc, char* argv[])
{
    if (argc == 1) {printf("USAGE: main.exe --generate\n");}
    else if (argc == 2 && strcmp(argv[2-1], "--generate") == 0) {rand_i64_write("out.bin", 1'000);}
    else if (argc == 3 && strcmp(argv[2-1], "--generate") == 0) {rand_i64_write("out.bin", atoi(argv[3-1]));}
}