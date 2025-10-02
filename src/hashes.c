#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashes.h"
#include "commands.h"

unsigned char* hash(char **array) {
    unsigned char seeds[16] = {};
    
    /* Fill seeds with ASCII */
    for (int i = 0; i < 16; i++) {
        seeds[i] = i + 65;
    }
    
    /* Do the hash thing */
    /* Outputs 128-bit hash */
    /* Note: this is not a very good hash function but it gets the job done (worse MD5?) */
    int array_len = arrnlen(array, 10);
    for (int i = 0; i < array_len; i++) {
        for (int j = 0; j < 16; j++) {
            int string_len = strlen(array[i]);
            seeds[j] = seeds[j] + (array[i][j % string_len] >> (j % 3));
        }
    }
    
    /* Return the hash */
    unsigned char* hash = (unsigned char*)malloc(sizeof(unsigned char) * 16);
    for (int i = 0; i < 16; i++) {
        hash[i] = seeds[i];
    }
    return hash;
}

void print_hash(unsigned char* hash) {
    for (int i = 0; i < 16; i++) {
        printf("%x", hash[i]);
    }
    printf("\n");
}