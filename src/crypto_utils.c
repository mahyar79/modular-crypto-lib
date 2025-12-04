#include <stdio.h>
#include "crypto_utils.h"
#include <stdint.h>

void xor_buffers(unsigned char *result,
    const unsigned char *a, const unsigned char *b, int len){
        for (int i = 0; i < len; i++)
            result [i] = a[i] ^ b[i];
    }
int main (){
    return 1;
}

uint32_t byte_swap_32(uint32_t val){
    uint32_t result = 0;

        result |= ( (val & 0xFF) << 24 );

        result |= ( (val >> 8) & 0xFF) << 16;
        //Original val: 10101010 10111011 11001100 11011101 (AA BB CC DD)
       // After >> 8:  00000000 10101010 10111011 11001100 (00 AA BB CC) ← DD is gone, AA/BB/CC shifted down.
        //result |= this: Current result (0xDD000000) OR 0x00CC0000 → 0xDDCC0000.

        result |= ( (val >> 16) & 0xFF) << 8;

        result |= (val >> 24) & 0xFF;

        return result;
}
