/*
** MYTEAMS PROJECT, 2024
** myteams
** File description:
** save
*/

#include <stdbool.h>
#include <stdio.h>

#include "database.h"
#include "libs/def.h"
#include "server.h"

static void save_dms(dm_t **dms)
{
    FILE *file = fopen(DATABASE_DIR "dms.txt", "w");
    bool passed = false;

    if (!file) {
        PERR_NORET("Open failed");
        return;
    }
    for (; *dms; dms++) {
        if (passed) {
            fprintf(file, "\n%s\n%s\n%ld\n%s", (*dms)->sender->uuid,
                (*dms)->receiver->uuid, (*dms)->time, (*dms)->message);
        } else {
            fprintf(file, "%s\n%s\n%ld\n%s", (*dms)->sender->uuid,
                (*dms)->receiver->uuid, (*dms)->time, (*dms)->message);
        }
        passed = true;
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
    bool passed = false;

    if (!file) {
        PERR_NORET("Open failed");
        return;
    }
    for (; *users; users++) {
        if (passed) {
            fprintf(file, "\n%s\n%s", (*users)->uuid, (*users)->name);
        } else {
            fprintf(file, "%s\n%s", (*users)->uuid, (*users)->name);
        }
        passed = true;
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
    static bool passed = false;

    fprintf(file, (passed) ? "\n%s\n%ld\n%s" : "%s\n%ld\n%s", rep->uuid,
        rep->time, rep->body);
    fclose(file);
    passed = true;
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
    static bool passed = false;

    fprintf(file,
        (passed) ? "\n%s\n%ld\n%s\n%s\nreplies" : "%s\n%ld\n%s\n%s\nreplies",
        th->uuid, th->time, th->title, th->message);
    for (reply_t **reps = th->replies; *reps; reps++) {
        fprintf(file, "\n\t%s", (*reps)->uuid);
        save_reply((*reps));
    }
    fclose(file);
    passed = true;
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
    static bool passed = false;

    fprintf(file, (passed) ? "\n%s\n%s\n%s\nthreads" : "%s\n%s\n%s\nthreads",
        ch->uuid, ch->name, ch->description);
    for (thread_t **threads = ch->threads; *threads; threads++) {
        fprintf(file, "\n\t%s", (*threads)->uuid);
        save_thread((*threads));
    }
    fclose(file);
    passed = true;
}

static void print_team_basic(FILE *file, team_t *team, bool passed)
{
    if (passed) {
        fprintf(file, "\n%s\n%s\n%s\n%s\nsubscribers", team->uuid, team->name,
            team->description, team->creator->uuid);
    } else {
        fprintf(file, "%s\n%s\n%s\n%s\nsubscribers", team->uuid, team->name,
            team->description, team->creator->uuid);
    }
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
    static bool passed = false;

    if (!file) {
        return PERR("Open failed");
    }
    for (; *teams; teams++) {
        print_team_basic(file, *teams, passed);
        for (user_t **users = (*teams)->subscribers; *users; users++)
            fprintf(file, "\n\t%s", (*users)->uuid);
        fprintf(file, "\nchannels");
        for (channel_t **ch = (*teams)->channels; *ch; ch++) {
            save_channel((*ch));
            fprintf(file, "\n\t%s", (*ch)->uuid);
        }
        passed = true;
    }
    fclose(file);
    return SUCCESS;
}

void save_database(server_t *server)
{
    FILE *file = NULL;

    file = fopen(DATABASE_DIR "teams.txt", "w");
    fclose(file);
    file = fopen(DATABASE_DIR "channels.txt", "w");
    fclose(file);
    file = fopen(DATABASE_DIR "threads.txt", "w");
    fclose(file);
    file = fopen(DATABASE_DIR "replies.txt", "w");
    fclose(file);
    save_users(server->users);
    save_dms(server->dms);
    save_all(server->teams);
}
