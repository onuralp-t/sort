#include <ctype.h>
#include <time.h>

#define COMMON_IMPLEMENTATION
#include "common.h"

void rand_i64_write(const char* dst_path, int64_t buffer_count, xo_state* rng_state)
{
    int64_t *array = (int64_t*)malloc(sizeof(int64_t) * buffer_count);

    for (int64_t i = 0; i < buffer_count; ++i)
    {
        array[i] = rand_xo(rng_state);
    }

    FILE *f = fopen(dst_path, "wb");
    fwrite(array, sizeof(int64_t), buffer_count, f);
    fclose(f);
}

int main(int argc, char* argv[])
{
    xo_state rng = {0};
    srand_xo(&rng, time(0));

    if (argc == 1) {printf("USAGE: ./bingen <number>\n");}
    else if (argc == 2)
    {
        char* arg = argv[2-1];
        while (*arg) {
            if (!isdigit(*arg)) {printf("USAGE: ./bingen <number>\n"); return 0;};
            ++arg;
        }

        rand_i64_write("out.bin", atoi(argv[2-1]), &rng);
        printf("INFO: wrote `%d` randomly generated 64-bit numbers to `out.bin`\n", atoi(argv[2-1]));
    }
    else {printf("USAGE: bingen.exe <number>\n");}

    return 0;
}