#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

#if 0
void main(void) {
    char* command[] = {"this", "is a", "test", NULL};
    char* command2[] = {"this", "isn't a", "test", NULL};
    char* command3[] = {NULL};
    unsigned char* hashout = hash(command);
    unsigned char* hashout2 = hash(command2);
    unsigned char* hashout3 = hash(command3);
    
    print_hash(hashout);
    printf("\n");
    print_hash(hashout2);
    printf("\n");
    print_hash(hashout3);
    printf("\n");
}
#endif