#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commands.h"
#include "linkedlist.h"

void main(void) {
    // Ask user for command
    // 'help' command not yet implemented
    printf("Enter FML command. Type 'help' for a list of commands\n");
    
    /* Initialize history */
    struct LinkedList *historyll = (struct LinkedList*)malloc(sizeof(struct LinkedList));
    init_ll(historyll);

    while (1) {
        //Recieve user input
        char input[255];
        char *token;
        printf("\n>> ");
        fgets(input, sizeof(input), stdin);
        
        //Split user input into array of char* pointers
        //Accepts maximum of MAX_COMMAND_LEN individual substrings
        char *command[MAX_COMMAND_LEN] = {};
        input[strcspn(input, "\n")] = 0;      //Removes newline from input
        token = strtok(input, " ");
        for (int i = 0; token != NULL && i < MAX_COMMAND_LEN; i++) {   // stops if there are 4 or more args passed
            command[i] = token;
            token = strtok(NULL, " \n");
        }
        
        //Parse command
        char *name = command[0];
        int return_code = -1;
        if (strcmp(name, "quit") == 0) {
            printf("Exiting...\n");
            break;
        }
        else if (strcmp(name, "upload") == 0) {
            return_code = upload(command);
        }
        else if (strcmp(name, "download") == 0) {
            return_code = download(command);
        }
        else if (strcmp(name, "delete") == 0) {
            return_code = delete(command);
        }
        else if (strcmp(name, "change") == 0) {
            return_code = change(command);
        }
        else if (strcmp(name, "show") == 0) {
            return_code = show(command);
        }
        else if (strcmp(name, "history") == 0) {
            return_code = history(command, historyll);
        }
        else if (strcmp(name, "validate") == 0) {
            return_code = validate(command);
        }
        else {
            printf("'%s' is not a valid FML command.\n", name);
            return_code = -1;
            continue;
        }
        
        /* Add command to history if valid */
        if (!return_code) {
            append(historyll, command);
            return_code = -1;
        }
    }
}