// eratosthenes
   // Řešení IJC-DU1, příklad a), 19.3.2025
   // Autor: Josef Pasek, FIT
   // Přeloženo: gcc 14.2.1
// eratosthenesovo sito implementace
#include "bitset.h"
#include "error.h"
void Eratosthenes(bitset_t jmeno_pole){
    bitset_fill(jmeno_pole, 1);
    bitset_setbit(jmeno_pole, 0,0);
    bitset_setbit(jmeno_pole, 1,0);
    size_t size = bitset_size(jmeno_pole);
    for (size_t i = 2; i * i <= size; i++) {
        if (bitset_getbit(jmeno_pole, i) == 1) {
            for (size_t j = i * i; j < size; j += i) {
                bitset_setbit(jmeno_pole, j, 0);

            }
        }
    }
    }
