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
