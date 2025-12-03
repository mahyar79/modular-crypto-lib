#include <stdio.h>
#include "crypto_utils.h"

void xor_buffers(unsigned char *result,
    const unsigned char *a, const unsigned char *b, int len){
        for (int i = 0; i < len; i++)
            result [i] = a[i] ^ b[i];
    }
int main (){
    return 1;
}
