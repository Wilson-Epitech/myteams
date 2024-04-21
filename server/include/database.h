/*
** MYTEAMS PROJECT, 2024
** myteams
** File description:
** database
*/

#pragma once

#include "server.h"

#define DATABASE_DIR "./database/"

// Save
void save_database(server_t *server);

// Load
reply_t **load_replies(user_t **users);
thread_t **load_threads(user_t **users);
channel_t **load_channels(user_t **users);
team_t **load_teams(user_t **users);
user_t **load_users(void);
dm_t **load_dms(user_t **users);
