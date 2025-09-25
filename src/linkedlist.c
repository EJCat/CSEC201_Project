#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

void init_ll(struct LinkedList* list) {
    list->size = 0;
    list->head = NULL;
}

void prepend(struct LinkedList* list, char* command[]) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->command = command;
    new_node->next = list->head;
    list->head = new_node;
    list->size++;
}

void append(struct LinkedList* list, char* command[]) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    struct Node* temp = list->head;
    char **cmdcpy = command;
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
        printf("  %d  %s\n", i, temp->command[0]);
        temp = temp->next;
        i++;
    }
}