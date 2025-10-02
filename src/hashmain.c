#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashes.h"

// void main(void) {
void not_main(void) {
    char* command[] = {"this", "is a", "test", NULL};
    char* command2[] = {"this", "isn't a", "test", NULL};
    unsigned char* hashout = hash(command);
    unsigned char* hashout2 = hash(command2);
    
    print_hash(hashout);
    print_hash(hashout2);
}