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

int check_location(char *array[]) {
    if (check_len(array, 2) < 0) {
        return 4;
    }
    
    if (strcmp(array[1], "local") == 0) {
        return 0;
    }
    else if (strcmp(array[1], "remote") == 0) {
        return 1;
    }
    else {
        return 3;
    }
}

int listpcmp(char search[], char* matches[], int size) {
    if (check_len(matches, size) < 0) { //Ensure 'matches' of length 'size' or greater
        return size;
    }

    for (int i=0; i<size; i++) { //Returns search term index in matches if found
        if (strcmp(search, matches[i]) == 0) {
            return i;
        }
    }
    
    return size; //Returns size if not found
}

int upload(char *array[MAX_COMMAND_LEN]) {
    if (check_len(array, 3) != 0) {
        printf("Syntax error: upload <local filename> <remote filename>\n"); 
        return 2;
    }
}

int download(char *array[MAX_COMMAND_LEN]) {
    int len_diff = check_len(array, 3);
    if (len_diff != 0) {
        printf("Syntax error: download <remote filename> <local filename>\n");
        return 2;
    }
}

int delete(char *array[MAX_COMMAND_LEN]) {
    int len_diff = check_len(array, 3);
    if (len_diff != 0) {
        printf("Syntax error: delete <local/remote> <filename>\n");
        return 2;
    }
    
    if (check_location(array) == 0) {
        // do local
    }
    else if (check_location(array) == 1) {
        // do remote
    }
    else {
        printf("'%s' is not a valid argument. Use 'local' or 'remote'.\n", array[1]);
        return 3;
    }
}

int change(char *array[MAX_COMMAND_LEN]) {
    int len_diff = check_len(array, 3);
    if (len_diff != 0) {
        printf("Syntax error: change <local/remote> <filepath>\n");
        return 2;
    }
    
    if (check_location(array) == 0) {
        // do local
    }
    else if (check_location(array) == 1) {
        // do remote
    }
    else {
        printf("'%s' is not a valid argument. Use 'local' or 'remote'.\n", array[1]);
        return 3;
    }
}

int show(char *array[MAX_COMMAND_LEN]) {
    int len_diff = check_len(array, 3);
    if (len_diff != 0) {
        printf("Syntax error: show <local/remote> <paths/files/folders>\n");
        return 2;
    }
    
    char* options[3] = {"paths", "files", "folders"};
    if (check_location(array) == 0) {                   //Local
        int i = listpcmp(array[2], options, 3);
        switch (i) {
            case 0:
                // do local paths
                break;
            case 1:
                //do local files
                break;
            case 2:
                //do local folders
                break;
            default:
                printf("'%s' is not a valid option. Use 'paths', 'files', or 'folders'.\n", array[2]);
                return 4;
        }
    }
    else if (check_location(array) == 1) {              //Remote
        int i = listpcmp(array[2], options, 3);
        switch (i) {
            case 0:
                // do remote paths
                break;
            case 1:
                //do remote files
                break;
            case 2:
                //do remote folders
                break;
            default:
                printf("'%s' is not a valid option. Use 'paths', 'files', or 'folders'.\n", array[2]);
                return 4;
        }
    }
    else {
        printf("'%s' is not a valid argument. Use 'local' or 'remote'.\n", array[1]);
        return 3;
    }
}

int history(char *array[MAX_COMMAND_LEN]) {
    int len_diff = check_len(array, 1);
    if (len_diff != 0) {
        printf("Syntax error: history does not take parameters");
        return 2;
    }
}

int validate(char *array[MAX_COMMAND_LEN]) {
    int len_diff = check_len(array, 1);
    if (len_diff != 0) {
        printf("Syntax error: validate does not take parameters");
        return 2;
    }
}