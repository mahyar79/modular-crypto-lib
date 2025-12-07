#include "bignum.h"
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

int bn_init(bn_t *bn,uint32_t capacity){
    bn -> digits = malloc(capacity * sizeof(uint32_t));
    if (bn -> digits == NULL)
        return -1;
    bn -> len = 0;
    bn -> capacity = capacity;
    return 0;
}

void bn_free(bn_t *n){
    free(n -> digits);
    n-> digits = NULL;
    n-> len = 0;
    n -> capacity = 0;
}

int bn_add(bn_t *r, const bn_t *a, const bn_t *b){
    size_t len = a -> len ; // for now assume that a and b have the same length
    uint32_t carry = 0;

    if (r-> capacity < len +1)
        return -1;

    for (size_t i = 0; i < len; i++){

        uint64_t temp_sum = (uint64_t) a -> digits[i] + b -> digits[i] + carry;
        uint32_t result_word = (uint32_t) temp_sum;
        carry = temp_sum >> 32;
        r -> digits[i] = result_word;
    }
    r-> len = len;
    if (carry != 0){
        r-> digits[len] = carry;
        r-> len++;
    }
    return 0;
}
