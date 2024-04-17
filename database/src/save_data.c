/*
** MYTEAMS PROJECT, 2024
** myteams
** File description:
** save
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <ctype.h>

#include "libs/def.h"
#include "server.h"
#include "database.h"

static int is_file(const char *filepath)
{
    struct stat file;

    if (stat(filepath, &file) == 0 && S_ISREG(file.st_mode))
        return 1;
    return 0;
}

int save_users(user_t **users)
{
    int fd = 0;
    char *path = "./database/data/users.txt";

    if (is_file(path) == 0)
        create_file(path);
    fd = open(path, O_RDWR | O_APPEND, 0644);
    if (fd == -1) {
        PERR_NORET("Open failed");
        return 84;
    }
    for (size_t i = 0; users[i] != NULL; i++) {
        dprintf(fd, "%s\n%s\n", users[i]->uuid, users[i]->name);
    }
    close(fd);
    return 0;
}

int save_reply(reply_t **reply)
{
    int fd = 0;
    char *path = "./database/data/reply.txt";

    if (is_file(path) == 0)
        create_file(path);
    fd = open(path, O_RDWR | O_APPEND, 0644);
    if (fd == -1) {
        PERR_NORET("Open failed");
        return 84;
    }
    for (size_t i = 0; reply[i] != NULL; i++) {
        dprintf(fd, "%s\n%s\r\n", reply[i]->uuid, reply[i]->body);
    }
    close(fd);
    return 0;
}

int save_threads(thread_t **thread)
{
    int fd = 0;
    char *path = "./database/data/threads.txt";

    if (is_file(path) == 0)
        create_file(path);
    fd = open(path, O_RDWR | O_APPEND, 0644);
    if (fd == -1) {
        PERR_NORET("Open failed");
        return 84;
    }
    for (size_t i = 0; thread[i] != NULL; i++) {
        dprintf(fd, "%s\n%ld\r\n%s\n%s\n", thread[i]->uuid,
            thread[i]->time, thread[i]->title, thread[i]->message);
    }
    close(fd);
    return 0;
}
