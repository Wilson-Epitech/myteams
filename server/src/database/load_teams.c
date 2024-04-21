/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** load_teams
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "database.h"
#include "libs/arr.h"
#include "libs/file.h"
#include "libs/mem.h"
#include "libs/str.h"
#include "server.h"

static bool is_channel(char *token)
{
    if (token == NULL) {
        return false;
    }
    if (token[0] != '\t') {
        return false;
    }
    return true;
}

static bool is_user(char *token)
{
    if (token == NULL) {
        return false;
    }
    if (token[0] != '\t') {
        return false;
    }
    return true;
}

static void add_channel(team_t *team, channel_t **channels, char *token)
{
    for (; strcmp(token, (*channels)->uuid) != 0; channels++) {
    }
    arr_pushback(&(team->channels), *channels);
}

static void add_subscribers(
    team_t *team, user_t **users, char **tokens, size_t *i)
{
    team->subscribers = arr_alloc(1);
    for (*i += 5; is_user(tokens[*i]); *i += 1) {
        arr_pushback(
            &(team->subscribers), find_user_by_uuid(users, tokens[*i] + 1));
    }
}

static void add_channels(
    team_t *team, channel_t **channels, char **tokens, size_t *i)
{
    team->channels = arr_alloc(1);
    for (*i += 1; is_channel(tokens[*i]); *i += 1) {
        add_channel(team, channels, tokens[*i] + 1);
    }
}

// uuid
// name
// description
// creator
// subscribers
//             subscriber uuid
//             subscriber uuid
// channels
//             channel uuid
//             channel uuid
team_t **load_teams(user_t **users)
{
    SMART char *text = get_content(DATABASE_DIR "teams.txt");
    SMART char **tokens = (text) ? split(text, '\n') : arr_alloc(1);
    SMART channel_t **channels = load_channels(users);
    team_t *curr = NULL;
    team_t **teams = arr_alloc(1);

    for (size_t i = 0; tokens[i];) {
        curr = alloc(sizeof(team_t), team_free);
        curr->uuid = strcreate(tokens[i]);
        curr->name = strcreate(tokens[i + 1]);
        curr->description = strcreate(tokens[i + 2]);
        curr->creator = find_user_by_uuid(users, tokens[i + 3]);
        add_subscribers(curr, users, tokens, &i);
        add_channels(curr, channels, tokens, &i);
        arr_pushback(&teams, curr);
    }
    return teams;
}
// curr->subscribers = arr_alloc(1);
// for (i += 5; is_user(tokens[i]); i++) {
//     arr_pushback(
//         &(curr->subscribers), find_user_by_uuid(users, tokens[i] + 1));
// }

// curr->channels = arr_alloc(1);
// for (i += 1; is_channel(tokens[i]); i++)
//     add_channel(curr, channels, tokens[i] + 1);
