#include "bignum.h"
#include <cstdint>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int bn_init(bn_t *bn,uint32_t capacity){
    bn -> digits = malloc(capacity * sizeof(uint32_t));
    if (bn -> digits == NULL)
        return -1;
    bn -> len = 1;
    bn -> digits[0] = 0;
    bn -> capacity = capacity;
    return 0;
}

void bn_free(bn_t *n){
    free(n -> digits);
    n-> digits = NULL;
    n-> len = 0;
    n -> capacity = 0;
}

int bn_normalize(bn_t *a){
    while ( a-> digits[a-> len -1] == 0 && a-> len > 1){
        a-> len--;
    }
    return 0;
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
    bn_normalize(r);
    return 0;
}

int bn_sub(bn_t *r, const bn_t *a, const bn_t *b){
    size_t len = a -> len; // For simplicity, assume A≥B and A.len=B.len=R.capacity
    uint32_t borrow = 0;
    // for now assume r-> capacity is sufficient.
    for (size_t i = 0; i< len; i++){
        uint32_t sub_amount = b-> digits[i] + borrow;
        if(a -> digits[i] < sub_amount){
            // borrow is needed here
            r-> digits[i] = a-> digits[i] - sub_amount;  // c's unsigned math handles the wrap
            borrow = 1;
        }
        else{
            r -> digits[i] = a -> digits[i] - sub_amount;
            borrow = 0;
        }
    }
    r-> len = a -> len;
    bn_normalize(r);
    return borrow;
}

int bn_mul(bn_t *r, const bn_t *a, const bn_t *b){
    if (r-> capacity < a-> len + b-> len)
        return -1;

    //r-> len = 0;
    memset(r-> digits, 0, (a-> len + b-> len) * sizeof(uint32_t));

    for (size_t i = 0; i< a-> len; i++){
        uint32_t carry =0;

        for (size_t j = 0; j < b-> len; j++){
            uint64_t temp_sum = (uint64_t) a-> digits[i] * b-> digits[j] + carry + r-> digits[i+j];
            r-> digits[i+j] = (uint32_t) temp_sum;
            carry = temp_sum >> 32;
    }
        r-> digits[i + b-> len] = carry;
    }
    r-> len = a-> len + b-> len;
    bn_normalize(r);
    return 0;
}

int bn_copy(bn_t *dest, const bn_t *src){
    if (dest-> capacity < src -> len)
        return -1;

    dest -> len = src -> len;
    memcpy(dest-> digits, src-> digits, src-> len * sizeof(uint32_t));
    bn_normalize(dest);
    return 0;
}

uint32_t bn_get_bit(const bn_t *a, size_t index){
   size_t w_idx = index / 32;
   size_t b_pos = index %32;
   if ( index > (32 * a-> len) -1)
       return 0;

   return (a -> digits[w_idx] >> b_pos) & 1;
}

int bn_cmp(const bn_t *a, const bn_t *b){
    if (a-> len != b-> len)
        return a-> len > b-> len ? 1 : -1;

    for (size_t i = a-> len -1; i-- > 0;){
        if (a-> digits[i] != b-> digits[i])
            return a-> digits[i] > b-> digits[i] ? 1: -1;

    }
    if (a-> digits[0] != b-> digits[0])
        return a-> digits[0] > b-> digits[0] ? 1 : -1;
    return 0;
}

int bn_mod_exp(bn_t *r, const bn_t *a, const bn_t *e, const bn_t *n) {

    bn_mont_ctx_t ctx;
    bn_init(&ctx.N, n-> len);
    bn_copy(&ctx.N, n);

}

// bn_add: require a->len == b->len for now.

//bn_sub: require a->len == b->len and a >= b.

// r must not alias a or b.
