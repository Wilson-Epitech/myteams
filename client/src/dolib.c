/*
** MYTEAMS PROJECT, 2024
** dolib.c
** File description:
** dolib.c
*/

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "../libs/myteams/logging_client.h"
#include "client.h"
#include "cmd.h"

static int len_for_malloc(char *buf, int in)
{
    bool open_close = false;
    int len = 0;
    int index = 0;

    for (int i = 0; buf[i] != 0; i++) {
        if (buf[i] == ']') {
            index += 1;
            open_close = false;
        }
        if (open_close && index == in)
            len += 1;
        if (buf[i] == '[')
            open_close = true;
    }
    return len;
}

char *search_at_info(char *buf, int in)
{
    bool open_close = false;
    int len = len_for_malloc(buf, in);
    char *user = malloc(sizeof(char) * (len + 1));
    int cnt = 0;

    for (int i = 0; buf[i] != 0; i++) {
        if (buf[i] == ']') {
            in -= 1;
            cnt = 0;
            open_close = false;
        }
        if (open_close && in == 0) {
            user[cnt] = buf[i];
            cnt += 1;
        }
        if (buf[i] == '[')
            open_close = true;
    }
    user[len] = 0;
    return user;
}

void do003(char *buf)
{
    char *user = search_at_info(buf, 0);
    char *uuid = search_at_info(buf, 1);

    client_event_logged_in(uuid, user);
    free(user);
    free(uuid);
    return;
}

void do004(char *buf)
{
    char *user = search_at_info(buf, 0);
    char *uuid = search_at_info(buf, 1);

    client_event_logged_out(uuid, user);
    free(user);
    free(uuid);
    return;
}

void do104(char *buf)
{
    (void)buf;
    client_error_unauthorized();
}

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
            client->name = search_at_info(buf, 0);
            client->uuid = search_at_info(buf, 1);
        }
    }
    return false;
}
