#include "bitset.h"
#include <stdio.h>
int main(){
        clock_t start_t, end_t;
        double total_t;
          start_t = clock();
        //I alloc a array of 000 where first index is number of them
        bitset_create(jmeno_pole, VELIKOST);
        //fill them with 1
        /* go thought the pole and for every i we check if is not 0
        * if so we find all of number which a diveded by it and set there
        * bit 0 because they cannt be prime numbers
        */
        Eratosthenes(jmeno_pole);
        unsigned long list[10];
        int count = 0;
        for (size_t i = ((jmeno_pole[0] - 1) / ULONG_SIZE) + 1; i > 0; i--) {
            for (int j = ((ULONG_SIZE) - 1); j >= 0; j--){
                if((jmeno_pole[i] & (1UL << j)) != 0){
                    size_t index = (i - 1) * ULONG_SIZE + j;
                    count++;
                    list[10 -count] = index;
                    if (count == 10) {
                        break;
                    }
                }
            }
            if (count == 10) {
                break;
            }
        }
        for(int i = 0;i < 10;i++){
            printf(" %lu \n",list[i]);
        }
           end_t = clock();
      total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
           fprintf(stderr,"Time=%.3g\n", total_t  );

}
