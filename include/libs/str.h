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
    doesnt support [\"]
*/
char **split_keep_quote(const char *str, char del);

/*
    append a char to a string
*/
char *stradd_c(char **str, char c);

/*
    create a string from init with the string destructor
*/
char *strcreate(const char *init);

/*
    create a string of len n from init with the string destructor
*/
char *strncreate(const char *init, size_t n);

/*
    append a string to a string
*/
char *stradd_s(char **str, char *add);

/*
    converts an int/unsigned int/long/unsigned long to a string (malloc it)
*/
char *str_int(int x);
char *str_uint(unsigned x);
char *str_long(long x);
char *str_ulong(unsigned long x);
