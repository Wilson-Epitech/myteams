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
reply_t **load_replies();
thread_t **load_threads();
// user_t **load_users();
// team_t **load_teams();
// channel_t **load_channel();
// thread_t **load_thread();
// reply_t **load_replies();
