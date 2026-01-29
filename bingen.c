#include <ctype.h>
#include <string.h>
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

char** next_arg(int *argc, char ***argv)
{
    if (*argc > 1) {*argc -= 1; return *argv += 1;}
    else {return 0;}
}

int main(int argc, char* argv[])
{
    xo_state rng = {0};
    srand_xo(&rng, time(0));

    const char* default_output = "out.bin";
    const char* usage_message  = "USAGE: ./bingen <number> [-o output_path]\n";

    uint64_t PRN_count = 0;

    if (next_arg(&argc, &argv)) {
        char* arg = *argv;
        while (*arg) {
            if (!isdigit(*arg)) {printf("%s", usage_message); return 0;};
            ++arg;
        } // is number
        PRN_count = atoi(*argv);

        if (next_arg(&argc, &argv))
        {
            if (strcmp(*argv, "-o") == 0)
            {
                if (next_arg(&argc, &argv)) {
                    char* arg = *argv;
                    while (*arg) {
                        if (!isalnum(*arg)) {printf("%s", usage_message); return 0;};
                        ++arg;
                    } // is alnum
                    rand_i64_write(*argv, PRN_count, &rng);
                    printf("INFO: wrote `%llu` randomly generated 64-bit numbers to `%s`\n", PRN_count, *argv);
                }
                else {printf("%s", usage_message);}
            }
        }
        else
        {
            rand_i64_write(default_output, PRN_count, &rng);
            printf("INFO: wrote `%llu` randomly generated 64-bit numbers to `%s`\n", PRN_count, default_output);
        }
    }
    else {printf("%s", usage_message);}

    return 0;
}