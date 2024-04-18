/*
** MYTEAMS PROJECT, 2024
** myteams
** File description:
** save
*/

#include <stdio.h>

#include "database.h"
#include "libs/def.h"
#include "server.h"

int save_users(user_t **users)
{
    FILE *file = fopen(DATABASE_DIR "users.txt", "w");

    if (!file) {
        PERR_NORET("Open failed");
        return FAILURE;
    }
    for (; *users; users++) {
        fprintf(file, "%s\n%s\n", (*users)->uuid, (*users)->name);
    }
    fclose(file);
    return 0;
}

// int save_reply(reply_t **reply)
// {
//     int fd = 0;
//     char *path = "./database/data/reply.txt";

//     if (is_file(path) == 0)
//         create_file(path);
//     fd = open(path, O_RDWR | O_APPEND, 0644);
//     if (fd == -1) {
//         PERR_NORET("Open failed");
//         return 84;
//     }
//     for (size_t i = 0; reply[i] != NULL; i++) {
//         dprintf(fd, "%s\n%s\r\n", reply[i]->uuid, reply[i]->body);
//     }
//     close(fd);
//     return 0;
// }

// int save_threads(thread_t **thread)
// {
//     int fd = 0;
//     char *path = "./database/data/threads.txt";

//     if (is_file(path) == 0)
//         create_file(path);
//     fd = open(path, O_RDWR | O_APPEND, 0644);
//     if (fd == -1) {
//         PERR_NORET("Open failed");
//         return 84;
//     }
//     for (size_t i = 0; thread[i] != NULL; i++) {
//         dprintf(fd, "%s\n%ld\r\n%s\n%s\n", thread[i]->uuid, thread[i]->time,
//             thread[i]->title, thread[i]->message);
//     }
//     close(fd);
//     return 0;
// }
