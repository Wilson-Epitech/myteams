/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** arr_shift
*/

#include "libs/arr.h"

void arr_shift_left(char **arr)
{
    do {
        arr[0] = arr[1];
        arr++;
    } while (*arr);
}
