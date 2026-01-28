
#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifndef U32_MAX
#define U32_MAX 0xFFFFFFFF
#endif
#ifndef BCRYPT_USE_SYSTEM_PREFERRED_RNG
#define BCRYPT_USE_SYSTEM_PREFERRED_RNG 2
#endif

#define WINAPI_ __attribute((dllimport,stdcall))
WINAPI_ int32_t BCryptGenRandom(void* z0, uint8_t* buf, uint32_t bufsize, uint32_t flags);

uint32_t rand32(uint32_t min, uint32_t max)
{
    uint32_t val = 0;
    BCryptGenRandom(NULL, (uint8_t*)&val, sizeof(val), BCRYPT_USE_SYSTEM_PREFERRED_RNG);
    double normal = ((double)val) / U32_MAX;
    assert(max > min);
    return (uint32_t)(normal * (max - min)) + min;
}

void rand32_write(const char* dst_path, uint32_t buffer_count)
{
    uint32_t *array = (uint32_t*)malloc(sizeof(uint32_t) * buffer_count);
    for (uint32_t i = 0; i < buffer_count; ++i)
    {
        array[i] = rand32(0, U32_MAX);
    }

    FILE *f = fopen(dst_path, "wb");
    fwrite(array, sizeof(uint32_t), buffer_count, f);
    fclose(f);
}

#define ARRAYLEN(x) (int)(sizeof((x)) / sizeof((x)[0]))

int main(int argc, char* argv[])
{
    if (argc == 1) {printf("USAGE: main.exe --generate\n");}
    else if (argc == 2 && strcmp(argv[2-1], "--generate") == 0) {rand32_write("out.bin", 1000);}

    alignas(uint32_t) uint8_t data[] = {
        #embed "out.bin" if_empty(0) // https://en.cppreference.com/w/c/preprocessor/embed
    };

    uint32_t *u32_view = (uint32_t*)data;
    uint32_t u32_count = ARRAYLEN(data) / 4;
    
    for (uint32_t i = 0; i < u32_count; ++i)
    {
        printf("[%d] = %u\n", i, u32_view[i]);
    }

}