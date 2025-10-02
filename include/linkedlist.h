#pragma once

struct Node {
    char** command;
    unsigned char* hash;
    struct Node* next;
};

struct LinkedList {
    int size;
    struct Node* head;
};


void init_ll(struct LinkedList*);
char** listcpy(char*[]);
void append(struct LinkedList*, char*[]);
void print_list(struct LinkedList*);
unsigned char* hash(char**);
unsigned char* hash_node(struct Node*);
void print_hash(unsigned char*);
int cmphash(unsigned char*, unsigned char*);