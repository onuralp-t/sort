
#include <stdio.h>
#include <stdint.h>

#ifndef U32_MAX
#define U32_MAX 0xFFFFFFFF
#endif
#ifndef BCRYPT_USE_SYSTEM_PREFERRED_RNG
#define BCRYPT_USE_SYSTEM_PREFERRED_RNG 2
#endif

#define WINAPI_ __attribute((dllimport,stdcall))
WINAPI_ int32_t BCryptGenRandom(void* z0, uint8_t* buf, uint32_t bufsize, uint32_t flags);

uint32_t rand32(uint32_t limit)
{
    uint32_t val = 0;
    BCryptGenRandom(NULL, (uint8_t*)&val, sizeof(val), BCRYPT_USE_SYSTEM_PREFERRED_RNG);
    double valf64 = (double)val / U32_MAX;
    return (uint32_t)(valf64 * limit);
}

int main()
{
    printf("hello %u", rand32(10));
}