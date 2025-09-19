#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const int MAX_COMMAND_LEN = 3;

int check_len(char*[], int);
void upload(char*[]);
void download(char*[]);
void delete(char*[]);
void change(char*[]);
void show(char*[]);
void history(char*[]);
void validate(char*[]);