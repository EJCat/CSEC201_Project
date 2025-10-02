#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"
#include "commands.h"

/* Initializes LinkedList with default values */
void init_ll(struct LinkedList* list) {
    list->size = 0;
    list->head = NULL;
}

/* Creates a copy of a char pointer array
Returns a char double pointer */
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

/**
 * Appends a char pointer array to the end of a LinkedList.
 * Updates the hash of the previous tail node with the data of the new tail node.
 */
void append(struct LinkedList* list, char* command[]) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    struct Node* temp = list->head;
    char **cmdcpy = lstcpy(command);
    new_node->command = cmdcpy;
    new_node->hash = hash(NULL);
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
        print_hash(temp->hash);             /* Debugging hashes */
        printf("\n");

        temp = temp->next;
        i++;
    }
}

unsigned char* hash(char **array) {
    unsigned char seeds[16] = {};
    
    /* Fill seeds with init values */
    for (int i = 0; i < 16; i++) {
        seeds[i] = i + 65;
    }
    
    /* Do the hash thing */
    /* Outputs 128-bit hash */
    /* Note: this is not a very good hash function but it gets the job done (worse MD5?) */
    int array_len = arrnlen(array, 10);
    for (int i = 0; i < array_len; i++) {
        for (int j = 0; j < 16; j++) {
            int string_len = strlen(array[i]);
            if (j % 4 == 0) {
                seeds[j] = seeds[j] + (array[i][j % string_len] >> (j % 3));
            } else if (j % 4 == 1) {
                seeds[j] = seeds[j] - (array[i][j % string_len] << (j % 3));
            } else if (j % 4 == 2) {
                seeds[j] = ~(seeds[j]) | (array[i][j % string_len] >> 2);
            } else {
                seeds[j] = ~(seeds[j]) & (array[i][j % string_len] << 1);
            }
        }
    }
    
    /* Return the hash */
    unsigned char* hash = (unsigned char*)malloc(sizeof(unsigned char) * 16);
    for (int i = 0; i < 16; i++) {
        hash[i] = seeds[i];
    }
    return hash;
}

unsigned char* hash_node(struct Node* node) {
    /*
    Computes both hashes of previous node and XOR's.
    Returns final computed hash.
    */

    unsigned char* command_hash = hash(node->command);
    unsigned char* prev_hash = node->hash;
    unsigned char* full_hash = (unsigned char*)malloc(sizeof(char*) * 16);
    for (int i = 0; i < 16; i++) {
        full_hash[i] = command_hash[i] + ~prev_hash[i];
    }
    free(command_hash);
    
    return full_hash;
}

void print_hash(unsigned char* hash) {
    for (int i = 0; i < 16; i++) {
        printf("%x", hash[i]);
    }
}

int cmphash(unsigned char* hash1, unsigned char* hash2) {
    for (int i = 0; i < 16; i ++) {
        if (hash1[i] != hash2[i]) return 0;
    }
    return 1;
}