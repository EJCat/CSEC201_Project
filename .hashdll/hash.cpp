#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined _WIN32
#define xprt extern "C" __declspec(dllexport)
#include <windows.h>
#elif defined __linux__
#define xprt extern "C"
#else
#define xprt
#endif

xprt unsigned char *hash(char **array)
{
    unsigned char seeds[16] = {};

    /* Fill seeds with init values */
    for (int i = 0; i < 16; i++) {
        seeds[i] = i + 65;
    }

    if (array == NULL) {
        return NULL;
    }

    int array_len = 0;
    for (int i = 0; array[i] != NULL && i < 10; i++) {
        array_len++;
    }

    /* Do the hash thing */
    /* Outputs 128-bit hash */
    /* Note: this is not a very good hash function but it gets the job done
     * (worse MD5?) */
    for (int i = 0; i < array_len; i++) {
        for (int j = 0; j < 16; j++) {
            int string_len = strlen(array[i]);
            if (j % 4 == 0) {
                seeds[j] = seeds[j] + (array[i][j % string_len] >> (j % 3));
            }
            else if (j % 4 == 1) {
                seeds[j] = seeds[j] - (array[i][j % string_len] << (j % 3));
            }
            else if (j % 4 == 2) {
                seeds[j] = ~(seeds[j]) | (array[i][j % string_len] >> 2);
            }
            else {
                seeds[j] = (seeds[j]) & (~array[i][j % string_len] << 1);
            }
        }
    }

    /* Return the hash */
    unsigned char *hash = (unsigned char *)malloc(sizeof(unsigned char) * 16);
    for (int i = 0; i < 16; i++) {
        hash[i] = seeds[i];
    }
    return hash;
}

xprt void print_hash(unsigned char *hash)
{
    for (int i = 0; i < 16; i++) {
        printf("%x", hash[i]);
    }
}

xprt int cmphash(unsigned char *hash1, unsigned char *hash2)
{
    for (int i = 0; i < 16; i++) {
        if (hash1[i] != hash2[i])
            return 0;
    }
    return 1;
}

#if defined WIN32
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
#endif
