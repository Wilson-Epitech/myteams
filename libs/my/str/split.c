/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** split
*/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "libs/arr.h"
#include "libs/mem.h"
#include "libs/str.h"

// the do exists because you want to add what you've parsed at the end
// in case the last char isnt a space (which happens often)
char **split(const char *str, char del)
{
    size_t count = strcount(str, del);
    char **arr = arr_alloc(count + 2);
    size_t index = 0;
    size_t len = 0;
    char *next = NULL;

    do {
        next = strchr(str, del);
        len = ((next == NULL) ? strlen(str) : (size_t)(next - str));
        arr[index] = ptr_alloc(sizeof(char) * (len + 1));
        strncpy(arr[index], str, len);
        arr[index][len] = '\0';
        index += 1;
        str += len + 1;
    } while (index <= count);
    return arr;
}

char **split_keep_quote(const char *str, char del)
{
    char **arr = arr_alloc(1);
    SMART char *token = strcreate("");
    bool in_quote = false;

    for (; *str; str++) {
        if (*str == '"') {
            in_quote = !in_quote;
            stradd_c(&token, '"');
            continue;
        }
        if (*str == del && !in_quote) {
            arr_pushback(&arr, strcreate(token));
            token[0] = 0;
            continue;
        }
        stradd_c(&token, *str);
    }
    arr_pushback(&arr, strcreate(token));
    return arr;
}
