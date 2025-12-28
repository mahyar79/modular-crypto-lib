#ifndef BIGNUM_H
#define BIGNUM_H
#include <cstdint>
#include <stddef.h>
#include <stdint.h>

typedef struct  {
    uint32_t *digits;
    size_t len;
    uint32_t capacity;
}   bn_t;

typedef struct {
    bn_t N; // modulus
    uint32_t n_inv; // Modular inverse: n' = -n^{-1} (mod 2^32)
    bn_t RR;   // R^2 mod n (used to convert into Montgomery domain)
} bn_mont_ctx_t;

int bn_init(bn_t *bn,uint32_t capacity);

void bn_free(bn_t *n);
int bn_normalize(bn_t *a);
int bn_add(bn_t *r, const bn_t *a, const bn_t *b);
int bn_sub(bn_t *r, const bn_t *a, const bn_t *b);
int bn_mul(bn_t *r, const bn_t *a, const bn_t *b);
int bn_copy(bn_t *dest, const bn_t *src);
uint32_t bn_get_bit(const bn_t *a, size_t index);
int bn_cmp(const bn_t *a, const bn_t *b);
int bn_mod_exp(bn_t *r, const bn_t *a, const bn_t *e, const bn_t *n);
#endif
