/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** get_content
*/

#include <stdio.h>
#include <stdlib.h>

#include "libs/file.h"
#include "libs/mem.h"

char *get_content(const char *filename)
{
    FILE *file = fopen(filename, "r");
    char *content = NULL;
    size_t size;

    if (file == NULL) {
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    rewind(file);
    content = alloc(size + 1, ptr_free);
    fread(content, sizeof(char), size, file);
    content[size] = '\0';
    fclose(file);
    return content;
}
