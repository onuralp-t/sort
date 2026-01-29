#define COMMON_IMPLEMENTATION
#include "common.h"

int main()
{
    uint64_t s;
    uint64_t e;

    time_count(&s);
    time_sleep_ms(1000);
    time_count(&e);

    double SECONDS = time_get_time(e, s, TIME_SECONDS);
    double MILISECONDS = time_get_time(e, s, TIME_MILISECONDS);
    double MICROSECONDS = time_get_time(e, s, TIME_MICROSECONDS);
    double NANOSECONDS = time_get_time(e, s, TIME_NANOSECONDS);

    printf("SECONDS:      %.17f\n", SECONDS);
    printf("MILISECONDS:  %.14f\n", MILISECONDS);
    printf("MICROSECONDS: %.11f\n", MICROSECONDS);
    printf("NANOSECONDS:  %.8f\n", NANOSECONDS);

    return 0;
}