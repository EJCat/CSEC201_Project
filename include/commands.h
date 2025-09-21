#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const int MAX_COMMAND_LEN = 4;

int check_len(char*[], int);
int check_location(char*[]);
int listpcmp(char[], char*[], int);
int upload(char*[]);
int download(char*[]);
int delete(char*[]);
int change(char*[]);
int show(char*[]);
int history(char*[]);
int validate(char*[]);