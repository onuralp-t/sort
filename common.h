#ifndef COMMON_H_
#define COMMON_H_

// ===== USAGE =====
/*
#define COMMON_IMPLEMENTATION
#include "common.h"

int main(void)
{
    int64_t data_size = 0;
    uint8_t* data;
    file_read("out.bin", &data, &data_size);
    int64_t *i64_view = (int64_t*)data;
    int64_t i64_view_count = data_size / sizeof(int64_t);
}
*/

#include <stdint.h>

#define ARRAY_LEN(x) (sizeof((x))/sizeof((x)[0]))

bool file_read(const char *source_filename, uint8_t** filebuffer, int64_t *filesize);
int64_t digit_count(int64_t v);
void printarr_i64(int64_t *arr, int64_t arr_size);
#endif // COMMON_H_

#ifdef COMMON_IMPLEMENTATION
#include <stdio.h>
#include <stdlib.h>

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

int64_t digit_count(int64_t v)
{
    if (v < 0) {
        // Handle INT64_MIN specifically to avoid overflow on negation
        if (v == INT64_MIN) return 20; 
        return digit_count(-v) + 1;
    }
    if (v < 10LL) return 1;
    if (v < 100LL) return 2;
    if (v < 1000LL) return 3;
    if (v < 10000LL) return 4;
    if (v < 100000LL) return 5;
    if (v < 1000000LL) return 6;
    if (v < 10000000LL) return 7;
    if (v < 100000000LL) return 8;
    if (v < 1000000000LL) return 9;
    if (v < 10000000000LL) return 10;
    if (v < 100000000000LL) return 11;
    if (v < 1000000000000LL) return 12;
    if (v < 10000000000000LL) return 13;
    if (v < 100000000000000LL) return 14;
    if (v < 1000000000000000LL) return 15;
    if (v < 10000000000000000LL) return 16;
    if (v < 100000000000000000LL) return 17;
    if (v < 1000000000000000000LL) return 18;
    return 19;
}

void printarr_i64(int64_t *arr, int64_t arr_size)
{
    uint8_t digits = digit_count(arr_size);
    for (int64_t i = 0; i < arr_size; ++i)
    {
        printf("[%*lld] = %lld\n", digits, i, arr[i]);
    }
}


#endif // COMMON_IMPLEMENTATION