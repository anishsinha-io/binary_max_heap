#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "heap.h"

enum heap_stat heap(struct heap *h, size_t data_size, cmpfunc comparator, printfunc printer) {
    if (!h) return H_NULLPTR_ERR;
    h->capacity   = 10;
    h->size       = 0;
    h->data       = malloc(sizeof(void *) * h->capacity);
    h->max        = NULL;
    h->comparator = comparator;
    h->printer    = printer;
    h->data_size  = data_size;
    return H_OK;
}

static int new_capacity(int capacity) {
    if (capacity < 10) return capacity * 2;
    if (capacity < 100) return (int) (capacity * 1.5);
    if (capacity < 1000) return (int) (capacity * 1.1);
    return (int) (capacity * 1.01);
}

static enum heap_stat heap_resize(struct heap *h, int new_capacity) {
    if (!h) return H_NULLPTR_ERR;
    if (new_capacity < 0) return H_INVALID_CAPACITY;
    h->data = realloc(h->data, sizeof(void *) * new_capacity);
    return H_OK;
}

enum heap_stat heap_insert(struct heap *h, void *key) {
    if (!h) return H_NULLPTR_ERR;
    if (h->capacity == h->size) if ((heap_resize(h, new_capacity(h->capacity))) != H_OK) return H_INSERT_ERR;
    h->data[h->size++] = key;
    int new_key_index  = h->size - 1;
    int swap_index     = (h->size - 1) / 2;
    while (h->comparator(h->data[new_key_index], h->data[swap_index]) > 0 && new_key_index != swap_index) {
        void *tmp = h->data[new_key_index];
        h->data[new_key_index] = h->data[swap_index];
        h->data[swap_index]    = tmp;
        new_key_index = swap_index;
        swap_index    = (int) (floor((double) new_key_index / 2));
    }
    return H_INSERT_OK;
}

enum heap_stat heap_delete(struct heap *h, void *buf) {
    if (!h || !buf) return H_NULLPTR_ERR;
    if (h->size == 0) return H_UNDERFLOW_ERR;
    memcpy(buf, h->data[0], h->data_size);
    h->data[0]           = h->data[h->size - 1];
    h->data[h->size - 1] = NULL;
    // free(h->data[h->size - 1]);
    h->size--;
    if (h->size < h->capacity / 2) if (heap_resize(h, h->capacity / 2) != H_OK) return H_DELETE_ERR;
    int root_index       = 0, itr = 1, swap_index = (int) pow(2, itr) - 1;
    while (swap_index < h->size && h->comparator(h->data[root_index], h->data[swap_index]) < 0) {

        void *tmp = h->data[root_index];
        h->data[root_index] = h->data[swap_index];
        h->data[swap_index] = tmp;
        root_index = swap_index;
        itr++;
        swap_index = (int) pow(2, itr) - 1;
    }
    return H_DELETE_OK;
}

void print_heap(struct heap *h) {
    for (int i = 0; i < h->size; i++) h->printer(h->data[i]);
}