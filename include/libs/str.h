/*
** MYTEAMS PROJECT, 2024
** my-ftp
** File description:
** str
*/

#pragma once

#include <stddef.h>

/*
    count the number of occurence of a char in a string
*/
size_t strcount(const char *s, char c);

/*
    apply a check on every char of a string
 */
int strall(const char *str, int (*fn)(char c));

/*
    concat 2 strings
*/
char *strconcat(const char *left, const char *right);

/*
    split a string according to a delimiter
*/
char **split(const char *str, char del);

/*
    split but not inside double-quotes
*/
char **split_teams(const char *str, char del);

/*
    append a char to a string
*/
char *stradd_c(char **str, char c);

/*
    create a string from init with the string destructor
*/
char *strcreate(const char *init);
