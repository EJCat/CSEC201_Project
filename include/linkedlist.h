#pragma once

struct Node {
    char command[200];
    struct Node* next;
};

struct LinkedList {
    int size;
    struct node* head;
};


void init_ll(struct LinkedList*);
void add_item(struct LinkedList*, char*);
void print_list(struct LinkedList*);