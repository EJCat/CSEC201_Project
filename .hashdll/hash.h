#ifndef HASHDLL_H
#define HASHDLL_H

#ifdef __cplusplus
extern "C" {
#endif

// Declare the functions that will be exported from the DLL
#ifdef _WIN32
#define DLL_EXPORT __declspec(dllimport)
#else
#define DLL_EXPORT
#endif

DLL_EXPORT unsigned char *hash(char **array);
DLL_EXPORT void print_hash(unsigned char *hash);
DLL_EXPORT int cmphash(unsigned char *hash1, unsigned char *hash2);

#ifdef __cplusplus
}
#endif

#endif
