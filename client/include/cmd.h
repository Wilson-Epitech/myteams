/*
** MYTEAMS PROJECT, 2024
** cmd.h
** File description:
** cmd.h
*/

#pragma once

#include <stddef.h>

char *search_at_info(char *buf, int index);

typedef struct cmd_s {
    const char *name;
    void (*function)(char *);
} cmd_t;

#define DECLARE(name) void name(char *)
#define BRACKET_LEFT {
#define BRACKET_RIGHT }
#define ARGUMENTS(name) BRACKET_LEFT #name, name BRACKET_RIGHT

DECLARE(do003);
DECLARE(do004);
DECLARE(do007);
DECLARE(do104);
DECLARE(do105);
DECLARE(do107);
DECLARE(do108);
DECLARE(do109);

static const cmd_t COMMANDS[] = {
    // Success
    ARGUMENTS(do003),
    ARGUMENTS(do004),
    ARGUMENTS(do007),
    // Error
    ARGUMENTS(do104),
    ARGUMENTS(do105),
    ARGUMENTS(do107),
    ARGUMENTS(do108),
    ARGUMENTS(do109),
};

static const size_t NB_COMMANDS = sizeof(COMMANDS) / sizeof(cmd_t);

// Done
// do003 client_event_logged_in
// do004 client_event_logged_out
// Todo
// client_channel_print_threads
// client_error_already_exist
// client_error_unauthorized
// client_error_unknown_channel
// client_error_unknown_team
// client_error_unknown_thread
// client_error_unknown_user
// client_event_channel_created
// client_event_private_message_received
// client_event_team_created
// client_event_thread_created
// client_event_thread_reply_received
// client_print_channel
// client_print_channel_created
// client_print_reply_created
// client_print_subscribed
// client_print_team
// client_print_team_created
// client_print_teams
// client_print_thread
// client_print_thread_created
// client_print_unsubscribed
// client_print_user
// client_print_users
// client_private_message_print_messages
// client_team_print_channels
// client_thread_print_replies
