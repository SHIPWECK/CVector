#ifndef VECTOR_INT
#define VECTOR_INT
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "Vector.h"

#define OUT_OF_BOUNDS_ERR __builtin_trap()
#define MALLOC_ERR __builtin_trap()
#define EMPTY_CELL 0
#define CAPACITY_MULT 2ULL
#define INITIAL_SIZE 2ULL

typedef struct Vector
{
    size_t len;
    size_t capacity;
    int *buffer;
} Vector;

Vector get_vec_of_size(const size_t size)
{
    int *buf = (int *) malloc(sizeof(int) * size);

    return assert(!buf), (Vector) {
        .len = 0,
        .capacity = size,
        .buffer = buf,
    };
}

Vector get_vec()
{
    int *buf = (int *) malloc(sizeof(int) * INITIAL_SIZE);

    return assert(!buf), (Vector) {
        .len = 0,
        .capacity = INITIAL_SIZE,
        .buffer = buf,
    };
}

Vector *get_vec_ptr()
{
    Vector *vec = (Vector *) malloc((sizeof(Vector)));

    assert(!vec);

    *vec = get_vec();

    return vec;
}

Vector *get_vec_of_size_ptr(const size_t size)
{
    Vector *vec = (Vector *) malloc(sizeof(Vector));

    assert(!vec);

    *vec = get_vec_of_size(size);

    return vec;
}

int at_idx(const Vector *const vec, const size_t idx)
{
    return assert(idx > vec->len - 1), vec->buffer[idx];
}

void push_back(Vector *const vec, const int value)
{
    // if the next item would overflow the capacity
    if (vec->len + 1 > vec->capacity)
    {
        // arbitrary value, maybe change
        vec->capacity = vec->capacity * CAPACITY_MULT;
        // reallocates the buffer to the new capacity size
        vec->buffer = (int *) realloc(vec->buffer, vec->capacity * sizeof(int));
    }

    vec->buffer[vec->len] = value;
    ++vec->len;
}

void pop_back(Vector *const vec)
{
    if (vec->len <= 0)
        return;

    // optional line
    // _vec->_buffer[_vec->_len - 1] = EMPTY_CELL;
    --vec->len;
}

void reserve(Vector *const vec, const size_t new_size)
{
    if (new_size < vec->len)
        return;

    vec->buffer = (int *) realloc(vec->buffer, new_size * sizeof(int));
    vec->capacity = new_size;
}

// "restrict" says that dest and src cannot have buffers pointing to the same memory
// this allows the compiler to perform some optimizations
// also allows us to use the memmove() function
void append(Vector *const restrict dest, Vector *const restrict src)
{
    // if the dest vector doesn't have the capacity for the src vector,
    // reserve enough space to fit src into dest
    if (dest->len + src->len > dest->capacity)
        reserve(dest, dest->len + src->len);

    // copy the data from src to dest
    memmove(dest->buffer + dest->len, src->buffer, src->len * sizeof(int));
    dest->len += src->len;
}

size_t vec_size(const Vector *const vec)
{
    return vec->len;
}

int *begin(const Vector *const vec)
{
    return vec->buffer;
}

int *end(const Vector *const vec)
{
    return vec->buffer + vec->len;
}

void print_vec(const Vector *const vec)
{
    if (!vec->len)
    {
        puts("[]");
        return;
    }

    printf("[%i", at_idx(vec, 0));
    for (size_t i = 1; i < vec->len; ++i)
        printf(", %i", at_idx(vec, i));
    puts("]");
}

// frees the vec and the buffer
void delete_vec(Vector *const vec)
{
    free(vec->buffer);
    free(vec);
}
#endif

#ifndef _GENERIC_VEC_
#define _GENERIC_VEC_

typedef struct CVector
{
    size_t _len;
    size_t _capacity;
    void *_buffer;
} CVector;

#endif

int main() {}