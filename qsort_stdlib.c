#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define ARRLEN(x) (sizeof((x))/sizeof((x)[0]))

bool file_read(const char *source_filename, uint8_t** filebuffer, int64_t *filesize)
{
    if (!source_filename || !filebuffer) {return false;}
    
    // FILE_OPEN
    FILE *f = fopen(source_filename, "rb");
    if (!f) {return false; }

    fseek(f, 0, SEEK_END);
    *filesize = ftell(f);
    fseek(f, 0, SEEK_SET);

    // MEMORY_ALLOCATION
    *filebuffer = (uint8_t *)malloc(*filesize + 1);

    if (!(*filebuffer)) {return false;}

    *(*filebuffer + *filesize) = '\0';

    fread(*filebuffer, sizeof(uint8_t), *filesize, f);

    fclose(f);
    return true;
}

int compare_ints(const void* a, const void* b)
{
    return (*(int64_t*)a > *(int64_t*)b) - (*(int64_t*)a < *(int64_t*)b);
}

int main(void)
{
    int64_t data_size = 0;
    uint8_t* data;
    file_read("out.bin", &data, &data_size);

    int64_t *bazinga32 = (int64_t*)data;
    int64_t bazinga32_count = data_size / sizeof(int64_t);

    qsort(bazinga32, bazinga32_count, sizeof(int64_t), compare_ints);

    for (int i=0; i<bazinga32_count; ++i)
    {
        printf("[%d] %lld\n", i, bazinga32[i]);
    }
}