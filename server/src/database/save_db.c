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

// user uuid
// user name
//
static void save_users(user_t **users)
{
    FILE *file = fopen(DATABASE_DIR "users.txt", "w");

    if (!file) {
        PERR_NORET("Open failed");
        return;
    }
    for (; *users; users++) {
        fprintf(file, "%s\n%s\n", (*users)->uuid, (*users)->name);
    }
    fclose(file);
    return;
}

// team uuid
// team name
// team description
// creator uuid
// subscriber
//     subscriber uuid
//     subscriber uuid
// channels
//     channel uuid
//     channel uuid
//
static void save_teams(team_t **teams)
{
    FILE *file = fopen(DATABASE_DIR "teams.txt", "w");

    if (!file) {
        PERR_NORET("Open failed");
        return;
    }
    for (; *teams; teams++) {
        fprintf(file, "%s\n%s\n%s\n%s\n", (*teams)->uuid, (*teams)->name,
            (*teams)->description, (*teams)->creator->uuid);
        fprintf(file, "subscribers\n");
        for (user_t **users = (*teams)->subscribers; *users; users++) {
            fprintf(file, "\t%s\n", (*users)->uuid);
        }
        fprintf(file, "channels\n");
        for (channel_t **ch = (*teams)->channels; *ch; ch++) {
            fprintf(file, "\t%s\n", (*ch)->uuid);
        }
        fprintf(file, "\n");
    }
    fclose(file);
    return;
}

// channel uuid
// channel name
// channel description
// threads
//         thread uuid
//         thread uuid
//
// static void save_channel(channel_t *channel)
// {
//     FILE *file = fopen(DATABASE_DIR "channels.txt", "w");

//     if (!file) {
//         PERR_NORET("Open failed");
//         return;
//     }
//     fprintf(file, "%s\n%s\n%s\n", channel->uuid, channel->name,
//         channel->description);
//     fprintf(file, "threads\n");
//     for (thread_t **threads = channel->threads; *threads; threads++) {
//         fprintf(file, "\t%s\n", (*threads)->uuid);
//     }
//     fprintf(file, "\n");
//     fclose(file);
//     return;
// }

void save_database(server_t *server)
{
    save_users(server->users);
    save_teams(server->teams);
}
