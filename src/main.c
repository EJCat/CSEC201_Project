#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commands.h"


void main(void) {
    // Ask user for command
    // 'help' command not yet implemented
    printf("Enter FML command. Type 'help' for a list of commands\n>> ");
    
    //Recieve user input
    char input[50];
    char *token;
    fgets(input, sizeof(input), stdin);
    
    //Split user input into array of char* pointers
    //Accepts maximum of MAX_COMMAND_LEN individual substrings
    char* command[MAX_COMMAND_LEN] = {};
    input[strcspn(input, "\n")] = 0;      //Removes newline from input
    token = strtok(input, " ");
    for (int i = 0; token != NULL; i++) {
        if (i == MAX_COMMAND_LEN) {       //Catch-all for commands that get passed too many arguments
            printf("Syntax error: Too many arguments passed. Max allowed = %d", MAX_COMMAND_LEN);
            return;
        }

        command[i] = token;
        printf("%s\n", command[i]);
        token = strtok(NULL, " \n");
    }
    
    //Parse command
    char *name = command[0];
    if (strcmp(name, "upload") == 0) {
        upload(command);
        int len = check_len(command, 2);
        printf("%d", len);
    } //add more commands
};