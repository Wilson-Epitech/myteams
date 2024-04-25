/*
** MYTEAMS PROJECT, 2024
** dolib.c
** File description:
** dolib.c
*/

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../libs/myteams/logging_client.h"
#include "client.h"
#include "cmd.h"
#include "libs/mem.h"
#include "libs/str.h"

char *get_info(char *buf, int index)
{
    char *info = strcreate("");
    int curr_index = -1;

    for (; *buf; buf++) {
        if (curr_index > index)
            break;
        if (curr_index == index && (strncmp(buf, "] ", 2) == 0)) {
            return info;
        }
        if (curr_index == index) {
            stradd_c(&info, *buf);
            continue;
        }
        if (strncmp(buf, " [", 2) == 0) {
            curr_index += 1;
            buf++;
        }
    }
    destroy(info);
    return NULL;
}

void do003(char *buf)
{
    SMART char *uuid = get_info(buf, 0);
    SMART char *name = get_info(buf, 1);

    client_event_logged_in(uuid, name);
    return;
}

void do004(char *buf)
{
    SMART char *uuid = get_info(buf, 0);
    SMART char *user = get_info(buf, 1);

    client_event_logged_out(uuid, user);
    return;
}

void do104(char *buf)
{
    (void)buf;
    client_error_unauthorized();
}

// printf("cmd=[%s]\n", buf);
bool dolibteams(client_t *client, char *buf)
{
    char str[6] = {0};

    str[0] = 'd';
    str[1] = 'o';
    for (size_t i = 0; i < 3; i++) {
        str[2 + i] = buf[i];
    }
    for (size_t i = 0; i < NB_COMMANDS; i++) {
        if (strcmp(str, "do004") == 0) {
            return true;
        }
        if (strcmp(COMMANDS[i].name, str) != 0)
            continue;
        COMMANDS[i].function(buf);
        if (strcmp(COMMANDS[i].name, "do003") == 0) {
            client->uuid = get_info(buf, 0);
            client->name = get_info(buf, 1);
        }
    }
    return false;
}
