#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <malloc.h>
#include <math.h>

#define fatal_error(fmt, ...)                   \
    do {                                        \
        printf(fmt "\n", ##__VA_ARGS__);        \
        exit(1);                                \
    } while (0)

typedef unsigned char byte;
typedef unsigned short ushort;
typedef unsigned int uint;

