#include "linkedlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Initializes LinkedList with default values */
void init_ll(struct LinkedList *list)
{
    list->size = 0;
    list->head = NULL;
}

/* Assumes NULL terminated array
Walks the array until it reaches NULL or provided 'max' */
int arrnlen(char *array[], int max)
{
    int count = 0;
    if (array == NULL) { /* Catches NULL pointers */
        return count;
    }
    for (int i = 0; i < max; i++) {
        if (array[i] == NULL) {
            break;
        }
        else {
            count++;
        }
    }
    return count;
}

/* Creates a copy of a char pointer array
Returns a char double pointer */
char **chrptr_arr_cpy(char **cmd)
{
    int count = 0;
    while (cmd[count] != NULL) {
        count++;
    }

    /* allocate length of cmd plus null byte */
    char **copy = malloc((count + 1) * sizeof(char *));
    for (int i = 0; i < count; i++) {
        /* allocate length of string plus null byte*/
        int len = strlen(cmd[i]) + 1;
        char *tok = malloc(len);
        strcpy(tok, cmd[i]);
        copy[i] = tok;
    }
    copy[count] = NULL;

    return copy;
}

/**
 * Appends a char pointer array to the end of a LinkedList.
 * Updates the hash of the previous tail node with the data of the new tail
 * node.
 */
void append(struct LinkedList *list, char **command)
{
    /* Check for NULL parameters */
    if (list == NULL || command == NULL) {
        return;
    }

    int count = 0;
    while (command[count] != NULL) {
        count++;
    }

    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    struct Node *temp = list->head;
    char **cmdcpy = chrptr_arr_cpy(command);
    new_node->command = cmdcpy;
    new_node->hash = hash(NULL);
    new_node->count = count;
    new_node->next = NULL;

    if (temp == NULL) {
        list->head = new_node;
        return;
    }
    else {
        while (temp->next != NULL) {
            temp = temp->next;
        }

        new_node->hash = hash_node(temp);

        temp->next = new_node;
    }
    list->size++;
}

struct Node *get_node(struct LinkedList *list, int index)
{
    if (index >= list->size || index < 0 || list->size == 0) {
        return NULL;
    }
    else if (index == 0) {
        return list->head;
    }

    struct Node *node = list->head;
    for (int i = 0; i < index; i++) {
        node = node->next;
    }
    return node;
}

void print_command(struct Node *node)
{
    if (node->command == NULL) {
        printf("NULL\n");
        return;
    }
    for (int i = 0; node->command[i] != NULL; i++) {
        printf("%s ", node->command[i]);
    }
    printf("\n");
}

void print_list(struct LinkedList *list)
{
    struct Node *temp = list->head;
    if (temp == NULL) {
        printf("No command history\n");
        return;
    }

    int i = 1;
    while (temp != NULL) {
        /* Print out command history in ascending order (ideally like bash
         * history) */
        printf("  %d  ", i);
        for (int j = 0; j < temp->count; j++) {
            printf("%s ", temp->command[j]);
        }

        temp = temp->next;
        i++;
    }
}

unsigned char *hash_node(struct Node *node)
{
    /*
    Computes both hashes of previous node and XOR's.
    Returns final computed hash.
    */

    unsigned char *command_hash = hash(node->command);
    unsigned char *prev_hash = node->hash;
    unsigned char *full_hash = (unsigned char *)malloc(sizeof(char *) * 16);
    for (int i = 0; i < 16; i++) {
        full_hash[i] = command_hash[i] + ~prev_hash[i];
    }
    free(command_hash);

    return full_hash;
}

int edit_node(struct Node *node, char **new_command, unsigned char *new_hash)
{
    if (new_command == NULL && new_hash == NULL) {
        node->command = NULL;
        return 0;
    }
    if (new_command != NULL) {
        node->command = new_command; /* Dangerous, only use for debugging, no sanitization*/
    }
    if (new_hash != NULL) {
        node->hash = new_hash;
    }
    return 0;
}

int del_node(struct LinkedList *list, int index)
{
    if (index >= list->size) { /* Return -1 if index out of bounds */
        return -1;
    }
    else if (index == 0) {
        struct Node *head = list->head;
        list->head = head->next;
        head->hash = hash(NULL);
        return 0;
    }

    struct Node *node = list->head;
    for (int i = 0; i < index - 1; i++) { /* Fetch node right before desired index */
        node = node->next;
    }

    struct Node *temp = node->next;
    node->next = temp->next;
    free(temp);
    return 0;
}

/**
 * Validates history LinkedLists of size 2 or greater
 * Returns -1 on success
 * Returns -2 if unable to validate
 * Returns index of unvalidated command otherwise
 */
int validate_list(struct LinkedList *list)
{
    if (list->size == 0 || list->head == NULL) {
        return -2;
    } /* Catch empty list */
    else if (list->size == 1) { /* Catch size 1 list */
        return -2;
    }

    struct Node *node = list->head;
    if (!cmphash(hash(NULL), node->hash)) { /* Validate list head */
        return 0;
    }

    int index = 0;
    while (node->next != NULL) { /* Blockchain hashing in reverse */
        struct Node *next_node = node->next;
        unsigned char *rehash = hash_node(node);
        if (!cmphash(rehash, next_node->hash)) {
            return index;
        }
        node = node->next;
        index++;
    }

    return -1;
}
