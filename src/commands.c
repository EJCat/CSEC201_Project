#include <stdio.h>
#include <stdlib.h>
#include "commands.h"

//Actual command function definitions

//Compares the length of the array with the given 'len' argument
//Returns 0 if size matches, or the difference otherwise
int check_len(char *array[], int len) {
    int count = 0;
    for (int i=0; i < MAX_COMMAND_LEN; i++) {
        if (array[i] != NULL) {
            count++;
        }
    }
    
    return count - len;
}

int upload(char *array[MAX_COMMAND_LEN]) {
    if (check_len(array, 3) != 0) {
        printf("Syntax error: upload <local filename> <remote filename>\n"); 
        return 2;
    }
}

int download(char *array[MAX_COMMAND_LEN]) {
    short len_diff = check_len(array, 3);
    if (len_diff != 0) {
        printf("Syntax error: download <remote filename> <local filename>\n");
        return 2;
    }
}

int delete(char *array[MAX_COMMAND_LEN]) {
    short len_diff = check_len(array, 3);
    if (len_diff != 0) {
        printf("Syntax error: delete <local/remote> <filename>\n");
        return 2;
    }
}

int change(char *array[MAX_COMMAND_LEN]) {
    short len_diff = check_len(array, 3);
    if (len_diff != 0) {
        printf("Syntax error: change <local/remote> <filepath>\n");
        return 2;
    }
}

int show(char *array[MAX_COMMAND_LEN]) {
    short len_diff = check_len(array, 3);
    if (len_diff != 0) {
        printf("Syntax error: show <local/remote> <paths/files/folders>\n");
        return 2;
    }
}

int history(char *array[MAX_COMMAND_LEN]) {
    short len_diff = check_len(array, 1);
    if (len_diff != 0) {
        printf("Syntax error: history does not take parameters");
        return 2;
    }
}