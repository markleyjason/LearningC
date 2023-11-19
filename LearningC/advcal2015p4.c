#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/md5.h>

char* str2md5(const char* str, int length) {
    int n;
    MD5_CTX c;
    unsigned char digest[16];
    char* out = (char*)malloc(33);

#pragma warning(suppress : 4996)
    MD5_Init(&c);

    while (length > 0) {
        if (length > 512) {
#pragma warning(suppress : 4996)
            MD5_Update(&c, str, 512);
        }
        else {
#pragma warning(suppress : 4996)
            MD5_Update(&c, str, length);
        }
        length -= 512;
        str += 512;
    }
#pragma warning(suppress : 4996)
    MD5_Final(digest, &c);

    for (n = 0; n < 16; ++n) {
        snprintf(&(out[n * 2]), 16 * 2, "%02x", (unsigned int)digest[n]);
    }

    return out;
}

int ad2015p4() {
    const char* starting_string = "bgvyzdsv";
    char* full_string;
    __int32 starts = 0;
    __int32 i = 0;
    __int32 string_size = 10;
    __int32 size = 1;
    __int32 count = 0;
    __int32 starting_zeroes = 6;


    while (!starts) {
        char* full_string = (char*)malloc(string_size);
        int t = strlen(starting_string);
        snprintf(full_string, string_size, "%s%d", starting_string, size);
        //printf("Full string: %s\n\n\n\n\n\n", full_string);
        char* output = str2md5(full_string, strlen(full_string));
        char md5string[33];
        
        //printf("Hash: %s\n", output);
        //if (size == 254575) {
          //  printf("Should be here");
        //}
        for (i = 0; i < starting_zeroes; i++) {
            if (output[i] == '0') {
                count++;
            }
        }
        if (count == starting_zeroes) {
            starts = 1;
        } else {
            starts = 0;
            count = 0;
            size++;
            if (size / ((string_size - 9) * 10) != 0) {
                string_size++;
            }
        }
        free(output);
    }
    
    printf("The first number is: %d\n", size);
    return 0;
}