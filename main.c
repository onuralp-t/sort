#include <stdlib.h>
#include <string.h>

#define COMMON_IMPLEMENTATION
#include "common.h"

int qsort_stdlib_comparator(const void* a, const void* b)
{
    return (*(int64_t*)a > *(int64_t*)b) - (*(int64_t*)a < *(int64_t*)b);
}
void qsort_stdlib(int64_t *i64_view, int64_t i64_view_count, int (*comparator)(const void *, const void *) )
{
    qsort(i64_view, i64_view_count, sizeof(int64_t), comparator);
}

int main(void)
{
    int64_t data_size = 0;
    uint8_t* data;
    file_read("out.bin", &data, &data_size);
    int64_t *i64_view = (int64_t*)data;
    int64_t i64_view_count = data_size / sizeof(int64_t);

    int64_t *qsort_stdlib_arr = (int64_t*)malloc(i64_view_count * sizeof(int64_t));
    int64_t qsort_stdlib_arr_size = i64_view_count;

    memcpy(qsort_stdlib_arr, i64_view, qsort_stdlib_arr_size * sizeof(int64_t));

    qsort_stdlib(qsort_stdlib_arr, qsort_stdlib_arr_size, qsort_stdlib_comparator);

    printarr(qsort_stdlib_arr, qsort_stdlib_arr_size);
}