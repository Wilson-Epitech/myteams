/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** mem
*/

#pragma once

#include <stddef.h>

// Smart pointer
#define SMART __attribute__((cleanup(auto_free)))

// Destructor type
typedef void (*destructor_t)(void *);

// Should never be called manually
void try_free(void *ptr);
void auto_free(void *ptr);
void *alloc(size_t size, destructor_t destructor);
void destroy(void *ptr);
void destroy_parent(void *ptr);

destructor_t get_destructor(void *ptr);
void set_destructor(void *ptr, destructor_t destructor);

// Constructor
void *ptr_alloc(size_t size);
void *arr_alloc(size_t len);

// Common Destructor
void ptr_free(void *ptr);
void arr_free(void *ptr);

// Pointer Arithmetic
size_t ptrlen(void *_ptr, size_t elem_size);

// Utils
void *alloc_resize(void *old, size_t n_elem_to_add, size_t elem_size);
void va_destroy(size_t n, ...);
