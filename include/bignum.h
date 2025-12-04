#ifndef BIGNUM_H
#define BIGNUM_H
#include <stddef.h>
#include <stdint.h>

typedef struct  {
    uint32_t *digits;
    size_t len;
    uint32_t capacity;
}   bn_t;

int bn_init(bn_t *bn,uint32_t capacity);
#endif
