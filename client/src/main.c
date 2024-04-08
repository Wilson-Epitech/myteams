/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** main
*/

#include <stdio.h>

#include "def.h"

int main(int argc, const char *argv[])
{
    printf("client\n");
    printf("argc=[%d]\n", argc);
    while (*argv) {
        printf("%s\n", *argv);
        argv++;
    }
    return SUCCESS;
}
