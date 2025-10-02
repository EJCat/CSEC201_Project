#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"
#include "commands.h"

void init_ll(struct LinkedList* list) {
    list->size = 0;
    list->head = NULL;
}

char** lstcpy(char* cmd[]) {
    int count = 0;
    while (cmd[count] != NULL) {
        count++;
    }
    
    char **copy = malloc((count + 1) * sizeof(char*));              /* allocate length of cmd plus null byte */
    for (int i = 0; i < count; i++) {
        int len = strlen(cmd[i]) + 1;           /* allocate length of string plus null byte*/
        char *tok = malloc(len);
        strcpy(tok, cmd[i]);
        copy[i] = tok;
    }
    copy[count] = NULL;
    
    return copy;
}

void append(struct LinkedList* list, char* command[]) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    struct Node* temp = list->head;
    char **cmdcpy = lstcpy(command);
    new_node->command = cmdcpy;
    new_node->next = NULL;
    
    if (temp == NULL) {
        list->head = new_node;
        return;
    }
    else {
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

void print_list(struct LinkedList* list) {
    struct Node* temp = list->head;
    if (temp == NULL) {
        printf("No command history\n");
        return;
    }

    int i = 1;
    while (temp != NULL) {
        /* Print out command history in ascending order (ideally like bash history) */
        printf("  %d  ", i);
        for (int j = 0; temp->command[j] != NULL; j++) {
            printf("%s ", temp->command[j]);
        }
        printf("\n");

        temp = temp->next;
        i++;
    }
}