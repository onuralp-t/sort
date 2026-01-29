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

typedef struct xo_state
{
	uint64_t s[4];
} xo_state;
void srand_xo(xo_state *state, uint64_t seed);
uint64_t rand_xo(xo_state *state);

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

static inline uint64_t splitmix64(uint64_t *state)
{
	uint64_t result = (*state += 0x9E3779B97F4A7C15);
	result = (result ^ (result >> 30)) * 0xBF58476D1CE4E5B9;
	result = (result ^ (result >> 27)) * 0x94D049BB133111EB;
	return result ^ (result >> 31);
}

static inline uint64_t rol64(uint64_t x, int k)
{
	return (x << k) | (x >> (64 - k));
}

uint64_t rand_xo(xo_state *state)
{
	uint64_t *s = state->s;
	uint64_t const result = rol64(s[0] + s[3], 23) + s[0];
	uint64_t const t = s[1] << 17;

	s[2] ^= s[0];
	s[3] ^= s[1];
	s[1] ^= s[2];
	s[0] ^= s[3];

	s[2] ^= t;
	s[3] = rol64(s[3], 45);

	return result;
}

void srand_xo(xo_state *state, uint64_t seed)
{
	uint64_t smstate = seed;

	uint64_t tmp = splitmix64(&smstate);
	state->s[0] = (uint32_t)tmp;
	state->s[1] = (uint32_t)(tmp >> 32);

	tmp = splitmix64(&smstate);
	state->s[2] = (uint32_t)tmp;
	state->s[3] = (uint32_t)(tmp >> 32);
}


#endif // COMMON_IMPLEMENTATION