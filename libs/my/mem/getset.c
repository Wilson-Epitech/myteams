/*
** MYTEAMS PROJECT, 2024
** my-ftp
** File description:
** ptr_type
*/

#include "libs/mem.h"

void set_destructor(void *ptr, destructor_t destructor)
{
    ((destructor_t *)ptr)[-1] = destructor;
}

destructor_t get_ptr_type(void *ptr)
{
    return ((destructor_t *)ptr)[-1];
}
