#include <stdio.h>
#include <stdlib.h>

#include "heap.h"

int compare_int(const void *first, const void *second) {
    return *(int *) first - *(int *) second;
}

void print_int(const void *key) {
    printf("%d ", *(int *) key);
}

int main() {
    struct heap test;
    heap(&test, sizeof(int), compare_int, print_int);
    int a = 5;
    int b = 10;
    int c = 2;
    int d = 3;
    int e = 13;
    int f = 46;
    int g = 1;
    int h = 2;
    int i = 3;
    int j = 9;
    int k = 8;
    int l = 4;
    int m = 6;
    int n = 8;
    int o = 10;
    heap_insert(&test, &a);
    heap_insert(&test, &b);
    heap_insert(&test, &c);
    heap_insert(&test, &d);
    heap_insert(&test, &e);
    heap_insert(&test, &f);
    heap_insert(&test, &g);
    heap_insert(&test, &h);
    heap_insert(&test, &i);
    heap_insert(&test, &j);
    heap_insert(&test, &k);
    heap_insert(&test, &l);
    heap_insert(&test, &m);
    heap_insert(&test, &n);
    heap_insert(&test, &o);
    print_heap(&test);
    printf("\n");
    void *buf = malloc(sizeof(int));
    heap_delete(&test, buf);
    print_heap(&test);
    printf("\n");
    printf("%d\n", *(int *) buf);
    return 0;
}
