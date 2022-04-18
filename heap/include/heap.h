#ifndef __HEAP__
#define __HEAP__

typedef int (*cmpfunc)(const void *, const void *);
typedef void(*printfunc)(const void *);

struct heap {
    int       size, capacity;
    void      *max;
    void      **data;
    size_t    data_size;
    cmpfunc   comparator;
    printfunc printer;
};

enum heap_stat {
    H_OK,
    H_INSERT_OK, H_INSERT_ERR,
    H_DELETE_OK, H_DELETE_ERR,
    H_UNDERFLOW_ERR, H_OVERFLOW_ERR,
    H_INVALID_CAPACITY,
    H_NULLPTR_ERR,
};

void print_heap(struct heap *h);

enum heap_stat heap(struct heap *h, size_t data_size, cmpfunc comparator, printfunc printer);
enum heap_stat heap_insert(struct heap *h, void *key);
enum heap_stat heap_delete(struct heap *h, void *buf);

#endif