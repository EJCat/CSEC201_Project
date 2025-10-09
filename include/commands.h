#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

static const int MAX_COMMAND_LEN = 4;

int arrnlen(char*[], int);
int check_len(char*[], int);
int check_location(char*[]);
int listpcmp(char[], char*[], int);
int upload(char*[]);
int download(char*[]);
int delete(char*[]);
int change(char*[]);
int show(char*[]);
int history(char*[], struct LinkedList*);
int validate(struct LinkedList*);