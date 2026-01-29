#include <stdlib.h>
#include <string.h>

#define COMMON_IMPLEMENTATION
#include "common.h"

int qsort_stdlib_comparator(const void* a, const void* b)
{
    return (*(int64_t*)a > *(int64_t*)b) - (*(int64_t*)a < *(int64_t*)b);
}
void qsort_stdlib(int64_t *data_i64, int64_t data_i64_count, int (*comparator)(const void *, const void *) )
{
    qsort(data_i64, data_i64_count, sizeof(int64_t), comparator);
}

typedef struct State
{
    union {
        uint8_t *data_u8;
        int64_t *data_i64;
    };

    int64_t count_u8;
    int64_t count_i64;
    
} State;

void state_copy(State *dst, State *src)
{
    dst->data_u8 = (uint8_t*)malloc(src->count_u8);
    dst->count_u8 = src->count_u8;
    dst->count_i64 = src->count_u8 / sizeof(int64_t);

    memcpy(dst->data_u8, src->data_u8, src->count_u8);
}

int main(void)
{
    State state = {0};
    file_read("out.bin", &state.data_u8, &state.count_u8);
    state.count_i64 = state.count_u8 / sizeof(int64_t);

    State qsort = {0};
    state_copy(&qsort, &state);

    qsort_stdlib(qsort.data_i64, qsort.count_i64, qsort_stdlib_comparator);

    printarr_i64(qsort.data_i64, qsort.count_i64);
}