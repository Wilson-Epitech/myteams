/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** cmd
*/

#pragma once

#include <stdlib.h>

#include "server.h"

#define MAX_NAME_LENGTH 32
#define MAX_DESCRIPTION_LENGTH 255
#define MAX_BODY_LENGTH 512

// 0000000000001520 T client_error_already_exist
// 00000000000014f0 T client_error_unauthorized
// 0000000000001460 T client_error_unknown_channel
// 0000000000001430 T client_error_unknown_team
// 0000000000001490 T client_error_unknown_thread
// 00000000000014c0 T client_error_unknown_user

// 0000000000001330 T client_channel_print_threads
// 0000000000001210 T client_event_channel_created
// 0000000000001120 T client_event_logged_in
// 0000000000001150 T client_event_logged_out
// 0000000000001180 T client_event_private_message_received
// 00000000000011e0 T client_event_team_created
// 0000000000001240 T client_event_thread_created
// 00000000000011b0 T client_event_thread_reply_received
// 00000000000015b0 T client_print_channel
// 0000000000001670 T client_print_channel_created
// 0000000000001700 T client_print_reply_created
// 0000000000001760 T client_print_subscribed
// 0000000000001580 T client_print_team
// 0000000000001640 T client_print_team_created
// 00000000000012d0 T client_print_teams
// 00000000000015e0 T client_print_thread
// 00000000000016a0 T client_print_thread_created
// 0000000000001790 T client_print_unsubscribed
// 0000000000001550 T client_print_user
// 00000000000012a0 T client_print_users
// 00000000000013e0 T client_private_message_print_messages
// 0000000000001300 T client_team_print_channels
// 0000000000001390 T client_thread_print_replies

// 0000000000001950 T server_event_user_logged_in
// 0000000000001980 T server_event_user_logged_out

// 00000000000018f0 T server_event_user_created
// 0000000000001920 T server_event_user_loaded

// 00000000000017f0 T server_event_channel_created
// 00000000000019b0 T server_event_private_message_sended
// 0000000000001860 T server_event_reply_created
// 00000000000017c0 T server_event_team_created
// 0000000000001820 T server_event_thread_created
// 0000000000001890 T server_event_user_subscribed
// 00000000000018c0 T server_event_user_unsubscribed

typedef struct cmd_s {
    const char *name;
    size_t argc;
    void (*function)(server_t *, client_t *, char **, size_t);
} cmd_t;

#define DECLARE(name) void name(server_t *, client_t *, char **, size_t)
#define BRACKET_LEFT {
#define BRACKET_RIGHT }
#define ARGUMENTS(name, argc) BRACKET_LEFT "/" #name, argc, name BRACKET_RIGHT

DECLARE(login);
DECLARE(logout);

static const cmd_t COMMANDS[] = {
    ARGUMENTS(login, 1),
    ARGUMENTS(logout, 0),
};

static const size_t NB_COMMANDS = sizeof(COMMANDS) / sizeof(cmd_t);
