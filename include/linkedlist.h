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
void print_command(struct Node*);
void print_list(struct LinkedList*);
unsigned char* hash(char**);
unsigned char* hash_node(struct Node*);
void print_hash(unsigned char*);
int cmphash(unsigned char*, unsigned char*);
int edit_node(struct Node*, char**, unsigned char*);
int del_node(struct LinkedList*, int);
int validate_list(struct LinkedList*);