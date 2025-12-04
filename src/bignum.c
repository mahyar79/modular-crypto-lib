#include "bignum.h"
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
