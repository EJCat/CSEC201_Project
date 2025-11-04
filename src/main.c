#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

static const int MAX_COMMAND_LEN = 4;

typedef struct LinkedList {
    int size;
    struct Node* head;
} LinkedList;

/* Assumes NULL terminated array 
Walks the array until it reaches NULL or provided 'max' */
int arrnlen(char *array[], int max) {
    int count = 0;
    if (array == NULL) { return count; }                /* Catches NULL pointers */
    for (int i = 0; i < max; i++) {
        if (array[i] == NULL) {
            break;
        } else {
            count++;
        }
    }
    return count;
}

/* Compares length of a pointer array with an expected value */
int check_len(char *array[], int expected) {
    int len = arrnlen(array, MAX_COMMAND_LEN);
    return len - expected;
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
    
    /* do stuff */

    return 0;
}

int download(char *array[MAX_COMMAND_LEN]) {
    int len_diff = check_len(array, 3);
    if (len_diff != 0) {
        printf("Syntax error: download <remote filename> <local filename>\n");
        return 2;
    }
    
    /* do stuff */

    return 0;
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
    
    /* do stuff */

    return 0;
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
    
    /* do stuff */

    return 0;
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
    
    /* do stuff */

    return 0;
}

int history(char *array[MAX_COMMAND_LEN], struct LinkedList* list) {
    int len_diff = check_len(array, 1);
    if (len_diff != 0) {
        printf("Syntax error: history does not take parameters");
        return 2;
    }

    print_list(list);
    validate(list);
}

int validate(struct LinkedList* list) {
    int index = validate_list(list);
    if (index < 0) {
        return 1;
    }
    printf("Can't validate command #%d\n  >>", index);
    print_command(get_node(list, index));

    return 0;
}

int main(void) {
    HINSTANCE ListDll = LoadLibrary("${workspaceFolder}\\lib\\linkedlist.dll");
    if (ListDll == NULL) {
        printf("DLL was not loaded... Exiting.");
        return 1;
    }


    typedef void (*init_ll)(LinkedList*);
    init_ll initfunc = (init_ll)GetProcAddress(ListDll, "init_ll");
    
    typedef void (*print_list)(LinkedList*);
    print_list printfunc = (print_list)GetProcAddress(ListDll, "print_list");


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
            return_code = validate(historyll);
        }
        else if (strcmp(name, "debugcmd") == 0) {
            printf("TEST VALIDATION 1 START - SHOULD THROW ERROR AT COMMAND #1 ONLY\n");
            struct LinkedList* templist = (struct LinkedList*)malloc(sizeof(struct LinkedList));
            init_ll(templist);
            char* command0[4] = {"cmd1", "arg2", "param3", NULL};
            char* command1[4] = {"ndfdf", "jfjdj", "nbcxsa", NULL};
            char* command2[4] = {"cmdcmdcdm", "argargarg", "parparpar", NULL};
            char* command3[4] = {"dmcdmcdmc", "gargargar", "rparparpa", NULL};
            append(templist, command0);
            append(templist, command1);
            append(templist, command2);
            append(templist, command3);
            del_node(templist, 2);
            validate(templist);
            free(templist);

            printf("TEST VALIDATION 2 START - SHOULD THROW ERROR AT COMMAND #0 ONLY\n");
            templist = (struct LinkedList*)malloc(sizeof(struct LinkedList));
            init_ll(templist);
            append(templist, command0);
            append(templist, command1);
            append(templist, command2);
            append(templist, command3);
            edit_node(get_node(templist, 0), NULL, NULL);
            validate(templist);
            free(templist);

            printf("TEST VALIDATION 3 START - SHOULD THROW ERROR AT COMMAND #1 ONLY\n");
            templist = (struct LinkedList*)malloc(sizeof(struct LinkedList));
            init_ll(templist);
            append(templist, command0);
            append(templist, command1);
            append(templist, command2);
            append(templist, command3);
            edit_node(get_node(templist, 1), NULL, NULL);
            edit_node(get_node(templist, 2), NULL, NULL);
            validate(templist);
            free(templist);
        }
        else if (strcmp(name, "debughash") == 0) {
            printf("TEST VALIDATION 1 START - SHOULD THROW ERROR AT COMMAND #1 ONLY\n");
            struct LinkedList* templist = (struct LinkedList*)malloc(sizeof(struct LinkedList));
            init_ll(templist);
            char* command0[4] = {"cmd1", "arg2", "param3", NULL};
            char* command1[4] = {"ndfdf", "jfjdj", "nbcxsa", NULL};
            char* command2[4] = {"cmdcmdcdm", "argargarg", "parparpar", NULL};
            char* command3[4] = {"dmcdmcdmc", "gargargar", "rparparpa", NULL};
            append(templist, command0);
            append(templist, command1);
            append(templist, command2);
            append(templist, command3);
            edit_node(get_node(templist, 2), NULL, hash(NULL));
            validate(templist);
            free(templist);

            printf("TEST VALIDATION 2 START - SHOULD THROW ERROR AT COMMAND #0 ONLY\n");
            templist = (struct LinkedList*)malloc(sizeof(struct LinkedList));
            init_ll(templist);
            append(templist, command0);
            append(templist, command1);
            append(templist, command2);
            append(templist, command3);
            edit_node(get_node(templist, 1), NULL, hash(NULL));
            edit_node(get_node(templist, 2), NULL, hash(NULL));
            validate(templist);
            free(templist);
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