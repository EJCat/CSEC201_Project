#pragma once

struct Node {
    char** command;
    char hash[17];
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