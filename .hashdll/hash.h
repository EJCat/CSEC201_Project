#ifndef HASH_H
#define HASH_H

#ifdef __cplusplus
extern "C" {
#endif

// Declare the functions that will be exported from the DLL
#ifdef HASHDLL_EXPORTS
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllimport)
#endif

#ifndef DLL_EXPORT
#define DLL_EXPORT
#endif

DLL_EXPORT unsigned char *hash(char **array);
DLL_EXPORT void print_hash(unsigned char *hash);
DLL_EXPORT int cmphash(unsigned char *hash1, unsigned char *hash2);

#ifdef __cplusplus
}
#endif

#endif
