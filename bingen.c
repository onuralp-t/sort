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

    const char* output_file   = "out.bin";
    const char* usage_message = "USAGE: ./bingen <number>\n";

    if (argc == 1) {printf("%s", usage_message); return 0;}
    else if (argc == 2)
    {
        char* arg = argv[2-1];
        while (*arg) {
            if (!isdigit(*arg)) {printf("%s", usage_message); return 0;};
            ++arg;
        }

        rand_i64_write(output_file, atoi(argv[2-1]), &rng);
        printf("INFO: wrote `%d` randomly generated 64-bit numbers to `%s`\n", atoi(argv[2-1]), output_file);
    }
    else {printf("%s", usage_message);}

    return 0;
}