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

void bn_free(bn_t *n);
int bn_add(bn_t *r, const bn_t *a, const bn_t *b);
int bn_sub(bn_t *r, const bn_t *a, const bn_t *b);
int bn_mul(bn_t *r, const bn_t *a, const bn_t *b);
#endif
