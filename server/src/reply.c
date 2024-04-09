/*
** MYTEAMS PROJECT, 2024
** my-ftp
** File description:
** reply
*/

#include "reply.h"

#include <string.h>
#include <unistd.h>

#include "libs/def.h"

int reply(int fd, const char *msg)
{
    if (write(fd, msg, strlen(msg)) == -1) {
        return FAILURE;
    }
    return SUCCESS;
}
