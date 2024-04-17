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

#include "../../include/libs/def.h"
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
    printf("path : %s\n", path);
    fd = open(path, O_RDWR | O_APPEND, 0644);
    if (fd == -1) {
        PERR_NORET("Open failed");
        return 84;
    }
    for (size_t i = 0; users[i] != NULL; i++) {
        dprintf(fd, "%s\n%s\t\n", users[i]->uuid, users[i]->name);
    }
    close(fd);
    return 0;
}
