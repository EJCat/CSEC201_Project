#pragma once

#ifndef HASH_H
#define HASH_H

#include <windows.h>

typedef unsigned char *(*hash_func_t)(char **);
typedef int (*cmphash_func_t)(unsigned char *, unsigned char *);

typedef struct {
    hash_func_t hash;
    cmphash_func_t cmphash;
} HashDLL;

#endif
