#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

void init_ll(struct LinkedList* list) {
    list->size = 0;
    list->head = NULL;
}

void add_item(struct LinkedList* list, char* command) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    strcpy(new_node->command, command);
    new_node->next = list->head;
    list->head = new_node;
    list->size++;
}

void print_list(struct LinkedList* list) {
    struct Node* temp = list->head;
    if (temp == NULL) {
        printf("No command history\n");
        return;
    }

    int i = 1;
    while (temp != NULL) {
        printf("  %d  %s\n", i, temp->command);
        temp = temp->next;
        i++;
    }
}