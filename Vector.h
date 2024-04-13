#ifndef VECTOR_INT
#define VECTOR_INT
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define EMPTY_CELL 0
#define CAPACITY_MULT 2
#define OUT_OF_BOUNDS_ERR *((char *)0) = '\0'
#define MALLOC_ERR *((char *)0) = '\0'

typedef struct Vector
{
    size_t len;
    size_t capacity;
    int *buffer;
} Vector;

extern Vector get_vec_of_size(const size_t);
extern Vector get_vec();
extern Vector *get_vec_ptr();
extern Vector *get_vec_of_size_ptr(const size_t);
extern int at_idx(const Vector *const _v, const size_t);
extern void push_back(Vector *const _v, const int);
extern void pop_back(Vector *const _v);
extern size_t vec_size(const Vector *const _v);
extern int *begin(const Vector *const _v);
extern int *end(const Vector *const _v);
extern void print_vec(const Vector *const _v);
extern void deleteVec(Vector * _v);

#endif