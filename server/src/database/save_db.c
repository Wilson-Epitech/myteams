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

static void save_dms(dm_t **dms)
{
    FILE *file = fopen(DATABASE_DIR "dms.txt", "w");

    if (!file) {
        PERR_NORET("Open failed");
        return;
    }
    for (; *dms; dms++) {
        fprintf(file, "%s\n%s\n%ld\n%s\n\n", (*dms)->sender->uuid,
            (*dms)->receiver->uuid, (*dms)->time, (*dms)->message);
    }
    fclose(file);
    return;
}

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
        fprintf(file, "%s\n%s\n\n", (*users)->uuid, (*users)->name);
    }
    fclose(file);
    return;
}

// reply uuid
// reply time
// reply body
static void save_reply(reply_t *rep)
{
    FILE *file = fopen(DATABASE_DIR "replies.txt", "a");

    fprintf(file, "%s\n%ld\n%s\n\n", rep->uuid, rep->time, rep->body);
    fclose(file);
}

// thread uuid
// thread time
// thread title
// thread message
// replies
//     reply uuid
//     reply uuid
static void save_thread(thread_t *th)
{
    FILE *file = fopen(DATABASE_DIR "threads.txt", "a");

    fprintf(file, "%s\n%ld\n%s\n%s\nreplies\n", th->uuid, th->time, th->title,
        th->message);
    for (reply_t **reps = th->replies; *reps; reps++) {
        fprintf(file, "\t%s\n", (*reps)->uuid);
        save_reply((*reps));
    }
    fprintf(file, "\n");
    fclose(file);
}

// channel uuid
// channel name
// channel description
// threads
//         thread uuid
//         thread uuid
//
static void save_channel(channel_t *ch)
{
    FILE *file = fopen(DATABASE_DIR "channels.txt", "a");

    fprintf(
        file, "%s\n%s\n%s\nthreads\n", ch->uuid, ch->name, ch->description);
    for (thread_t **threads = ch->threads; *threads; threads++) {
        fprintf(file, "\t%s\n", (*threads)->uuid);
        save_thread((*threads));
    }
    fprintf(file, "\n");
    fclose(file);
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
static int save_all(team_t **teams)
{
    FILE *file = fopen(DATABASE_DIR "teams.txt", "w");

    if (!file) {
        return PERR("Open failed");
    }
    for (; *teams; teams++) {
        fprintf(file, "%s\n%s\n%s\n%s\n", (*teams)->uuid, (*teams)->name,
            (*teams)->description, (*teams)->creator->uuid);
        fprintf(file, "subscribers\n");
        for (user_t **users = (*teams)->subscribers; *users; users++)
            fprintf(file, "\t%s\n", (*users)->uuid);
        fprintf(file, "channels\n");
        for (channel_t **ch = (*teams)->channels; *ch; ch++) {
            save_channel((*ch));
            fprintf(file, "\t%s\n", (*ch)->uuid);
        }
        fprintf(file, "\n");
    }
    fclose(file);
    return SUCCESS;
}

void save_database(server_t *server)
{
    FILE *file = NULL;

    save_users(server->users);
    file = fopen(DATABASE_DIR "teams.txt", "w");
    fclose(file);
    file = fopen(DATABASE_DIR "channels.txt", "w");
    fclose(file);
    file = fopen(DATABASE_DIR "threads.txt", "w");
    fclose(file);
    file = fopen(DATABASE_DIR "replies.txt", "w");
    fclose(file);
    save_all(server->teams);
    save_dms(server->dms);
}
