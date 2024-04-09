/*
** MYTEAMS PROJECT, 2024
** my-ftp
** File description:
** auto_free
*/

#include "libs/mem.h"

void auto_free(void *ptr)
{
    destroy(*(void **)ptr);
}
