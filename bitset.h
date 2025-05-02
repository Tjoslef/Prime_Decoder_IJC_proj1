// bitset.h
   // Řešení IJC-DU1, příklad a)b), 19.3.2025
   // Autor: Josef Pasek, FIT
   // Přeloženo: gcc 14.2.1
// header soubor pro alokace a s funkcemi pro spravu bitove pole
#include "error.h"
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stddef.h>
#include <limits.h>
#define ULONG_SIZE (sizeof(unsigned long) * CHAR_BIT)
#define VELIKOST 333000000
typedef unsigned long bitset_index_t;
typedef bitset_index_t*  bitset_t;
#define bitset_create(jmeno_pole,velikost) \
    static_assert((velikost) > 0, "Bitset size must be greater than 0"); \
    bitset_index_t jmeno_pole##_array[((velikost - 1) / ULONG_SIZE) + 1]; \
    memset(jmeno_pole##_array, 0, (((velikost - 1) / ULONG_SIZE) + 1) * sizeof(bitset_index_t));\
    jmeno_pole##_array[0] = velikost; \
    bitset_t jmeno_pole = jmeno_pole##_array;
#define bitset_alloc(jmeno_pole, velikost) \
   assert((velikost) > 0 && "Bitset size must be greater than 0"); \
   bitset_t jmeno_pole = calloc((((velikost - 1) / ULONG_SIZE) + 2), sizeof(bitset_index_t)); \
    if ((jmeno_pole) == NULL) { \
        error_exit("bitset_alloc: Chyba alokace paměti"); \
    } \
    jmeno_pole[0] = velikost;
#define bitset_free(jmeno_pole) do { \
    free(jmeno_pole); \
    jmeno_pole = NULL; \
} while(0)
#ifdef USE_INLINE
inline bitset_index_t bitset_size(bitset_t jmeno_pole){
return ((jmeno_pole)[0]);

}
inline bitset_t bitset_fill(bitset_t jmeno_pole,int bool_vyraz)  {
    size_t size = bitset_size(jmeno_pole);
    if (bool_vyraz) {
        for (size_t i = 0; i < size; i++) {
            jmeno_pole[1 + (i / ULONG_SIZE)] |= (1UL << (i % ULONG_SIZE));
        }

    } else {
        for (size_t i = 0; i < size; i++) {
            jmeno_pole[1 + (i / ULONG_SIZE)] &= ~(1UL << (i % ULONG_SIZE));
        }
    }
    return jmeno_pole;
}
inline bitset_t bitset_setbit(bitset_t jmeno_pole,size_t index,int bool_vyraz){
    if ((index) >= (jmeno_pole)[0]) {
        return(error_exit("bitset_setbit: Index out of range"),NULL);
    }
    if (bool_vyraz){
        (jmeno_pole)[1 + (index) / ULONG_SIZE] |= (1UL << ((index) % ULONG_SIZE));
    }
    else{
        (jmeno_pole)[1 + (index) / ULONG_SIZE] &= ~(1UL << ((index) % ULONG_SIZE));
    }
    return jmeno_pole;
}
inline int bitset_getbit(bitset_t jmeno_pole,size_t index){
    if((index) >= jmeno_pole[0]) {
        (error_exit("bitset_getbit: Index out of range"));
        return 0;
        }
       else{
        return ((jmeno_pole[1 + (index) / ULONG_SIZE] & (1UL << ((index) % ULONG_SIZE))) != 0);
        }
}
#else
#define bitset_size(jmeno_pole) ((jmeno_pole)[0])
#define bitset_fill(jmeno_pole, bool_vyraz) do { \
    size_t size = jmeno_pole[0]; \
    if (bool_vyraz) { \
        for (size_t i = 0; i < size; i++) { \
            size_t index = 1 + (i / ULONG_SIZE ); \
            jmeno_pole[index] |= (1UL << (i % ULONG_SIZE)); \
        } \
    } else { \
        for (size_t i = 0; i < size; i++) { \
            size_t index = 1 + (i / ULONG_SIZE); \
            jmeno_pole[index] &= ~(1UL << (i % ULONG_SIZE)); \
        } \
    } \
} while(0)
#define bitset_setbit(jmeno_pole, index, bool_vyraz) do { \
    if ((index) >= (jmeno_pole)[0]) error_exit("bitset_setbit: Index out of range"); \
    if (bool_vyraz) \
        (jmeno_pole)[1 + (index) / ULONG_SIZE ] |= (1UL << ((index) % ULONG_SIZE)); \
    else \
        (jmeno_pole)[1 + (index) / ULONG_SIZE] &= ~(1UL << ((index) % ULONG_SIZE)); \
} while(0)
#define bitset_getbit(jmeno_pole, index) \
    ((index) >= jmeno_pole[0] ? \
        (error_exit("bitset_getbit: Index out of range"), 0) : \
        ((jmeno_pole[1 + (index) / ULONG_SIZE] & (1UL << ((index) % ULONG_SIZE))) != 0))
#endif
void Eratosthenes(bitset_t jmeno_pole);
unsigned char *utf8_check(unsigned char *s);
