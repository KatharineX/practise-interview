#ifndef UNROLLED_H
#define UNROLLED_H

#include <stdlib.h>
#include <pthread.h>

struct unrolled_ll;

struct unrolled_ll* unrolled_ll_new(size_t n);
void unrolled_ll_append(struct unrolled_ll* list, 
    void* element);
void* unrolled_ll_remove(struct unrolled_ll* list, size_t i);
void* unrolled_ll_get(struct unrolled_ll* list, size_t i);
void unrolled_ll_destroy(struct unrolled_ll* list);

#endif