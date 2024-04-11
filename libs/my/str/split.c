/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** split
*/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "libs/mem.h"
#include "libs/str.h"

// the do exists because you want to add what you've parsed at the end
// in case the last char isnt a space (which happens often)
char **split(const char *str, char del)
{
    size_t count = strcount(str, del);
    char **arr = arr_alloc(sizeof(char *), count + 2);
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

// this split is made for my_teams in tek2
// it can split with double quotes around strings
// it keeps the double quote around the strings
// because the command name must not be in double quote
// ex:
// /set "12" "45" "67"
// -> [/set] ["12"] ["45"] ["67"]
// usually, you dont want to keep double quotes around string
// so the use-case of this split if very rare.
char **split_teams(const char *str, char del)
{
    char **arr = arr_alloc(sizeof(char *), 1);
    size_t index = 0;
    SMART char *token = strcreate("");
    bool in_quote = false;

    for (; *str; str++) {
        in_quote = *str == '"' ? !in_quote : in_quote;
        if (*str == del && !in_quote) {
            arr = alloc_resize(arr, 1, sizeof(char *));
            arr[index] = strcreate(token);
            token[0] = 0;
            index++;
            continue;
        }
        stradd_c(&token, *str);
    }
    arr = alloc_resize(arr, 1, sizeof(char *));
    arr[index] = strcreate(token);
    return arr;
}
