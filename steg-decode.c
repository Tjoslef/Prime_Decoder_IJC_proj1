// steg-decode.c
   // Řešení IJC-DU1, příklad b), 16.3.2025
   // Autor: Josef Pasek, FIT
   // Přeloženo: gcc 14.2.1
// decryptovani obrazku na vyslednou spravu
#include "ppm.h"
#include "bitset.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#define START_PRIME 101
#ifdef USE_INLINE
extern bitset_t bitset_fill(bitset_t jmeno_pole,int bool_vyraz);
extern bitset_index_t bitset_size(bitset_t jmeno_pole);
extern int bitset_getbit(bitset_t jmeno_pole,size_t index);
extern bitset_t bitset_setbit(bitset_t jmeno_pole,size_t index,int bool_vyraz);
#endif
int main(int argc,char *argv[]){
    if(argc < 2){
        error_exit("no enought input \n");
    }
    struct ppm *my_struct;
    my_struct = ppm_read(argv[1]);
    if(my_struct == NULL){
        warning("something goes wrong in  ");
    }
    size_t size = my_struct->xsize *my_struct->ysize * 3;
    bitset_alloc(image_bit, size);
    image_bit[0] = size;
    Eratosthenes(image_bit);
    unsigned char *story_c = calloc(size,CHAR_BIT);
    if(story_c == NULL){
        bitset_free(image_bit);
        error_exit("wrong malloc");
    }
    char c = 0;
    int index_bit = 0;
    int end_c = 0;
    size_t index_array = 0;
for (size_t i = START_PRIME; i < image_bit[0]; i++) {
    if (bitset_getbit(image_bit, i) == 1) {
        c |= (my_struct->data[1+i] & 1) << index_bit++;

        if (index_bit == CHAR_BIT) {
            if (c == '\0') {
                story_c[index_array] = '\0';
                end_c = 1;
                break;
            }
            story_c[index_array++] = c;
            c = 0;
            index_bit = 0;
        }
    }
}
    if(end_c ==0){
        error_exit("message dont have correct end character");
    }else {
        unsigned char *story_c1 = realloc(story_c, (index_array + 1) * sizeof(char));
        if (story_c1 == NULL) {
            bitset_free(image_bit);
            error_exit("realloc failed");
        }
        story_c = story_c1;
        printf("%s",story_c);
        printf("\n");
        if (utf8_check(story_c) != NULL) {
            bitset_free(image_bit);
            ppm_free(my_struct);
            free(story_c);
            error_exit("Message is not valid UTF-8");
        }
    }
    free(story_c);
    bitset_free(image_bit);
    ppm_free(my_struct);
}
