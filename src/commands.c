#include <stdio.h>
#include <stdlib.h>
#include "commands.h"

//Actual command function definitions

//Compares the length of the array with the given 'len' argument
//Returns 0 if size matches, or the difference otherwise
int check_len(char *array[], int len) {
    printf("%p->%p\n", array, *array);
    int count = 0;
    for (int i=0; i < MAX_COMMAND_LEN; i++) {
        if (array[i] != NULL) {
            printf("%s->%c\n", array[i], *array[i]);
            count++;
        }
    }
    
    return count - len;
}

void upload(char *array[MAX_COMMAND_LEN]) {
    if (check_len(array, 2) == 0) {
        printf("Upload has been given 2 arguments. Good job!\n"); 
    }
    else {
        printf("Upload has the wrong amount of arguments. You had %d too many :(\n", check_len(array, 2));
    }
}