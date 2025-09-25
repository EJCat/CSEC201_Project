#pragma once

struct Node {
    char command[255];
    struct Node* next;
};

struct LinkedList {
    int size;
    struct node* head;
};


void init_ll(struct LinkedList*);
void prepend(struct LinkedList*, char*);
void append(struct LinkedList*, char*);
void print_list(struct LinkedList*);