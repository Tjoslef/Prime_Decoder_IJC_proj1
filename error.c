// error.c
   // Řešení IJC-DU1, příklad a)/b), 13.3.2025
   // Autor: Josef Pasek, FIT
   // Přeloženo: gcc 14.2.1
// eratosthenesovo sito implementace
#include "error.h"
void warning(const char *fmt, ...){
    va_list args;
    va_start(args, fmt);
    fprintf(stderr,"Warning: ");
    vfprintf(stderr, fmt, args);
    va_end(args);
}
void error_exit(const char *fmt, ...){
    va_list args;
    va_start(args, fmt);
    fprintf(stderr,"Error: ");
    vfprintf(stderr, fmt, args);
    va_end(args);
    exit(1);
}
