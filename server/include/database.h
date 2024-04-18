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
reply_t **load_replies(void);
thread_t **load_threads(void);
// user_t **load_users();
// team_t **load_teams();
// channel_t **load_channel();
// dm_t **load_dms();
