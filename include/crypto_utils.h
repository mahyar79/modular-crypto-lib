#ifndef CRYPTO_UTILS_H
#define CRYPTO_UTILS_H
#include <stdint.h>


void xor_buffers(unsigned char *result,
                 const unsigned char *a,
                 const unsigned char *b,
                 int len);

uint32_t byte_swap_32(uint32_t val);
#endif
