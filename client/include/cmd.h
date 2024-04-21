/*
** MYTEAMS PROJECT, 2024
** cmd.h
** File description:
** cmd.h
*/

#pragma once

#include <stddef.h>

char *get_info(char *buf, int index);

typedef struct cmd_s {
    const char *name;
    void (*function)(char *);
} cmd_t;

#define DECLARE(name) void name(char *)
#define BRACKET_LEFT {
#define BRACKET_RIGHT }
#define ARGUMENTS(name) BRACKET_LEFT #name, name BRACKET_RIGHT

// Success
DECLARE(do003);
DECLARE(do004);
DECLARE(do007);
DECLARE(do009);
DECLARE(do010);
DECLARE(do011);
DECLARE(do023);
DECLARE(do024);
DECLARE(do025);
DECLARE(do026);
DECLARE(do027);
DECLARE(do028);
DECLARE(do036);

// Error
DECLARE(do104);
DECLARE(do105);
DECLARE(do107);
DECLARE(do108);
DECLARE(do109);

static const cmd_t COMMANDS[] = {
    // Success
    ARGUMENTS(do003), /* login */
    ARGUMENTS(do004), /* logout */
    ARGUMENTS(do007), /* users */
    ARGUMENTS(do009), /* create team */
    ARGUMENTS(do010), /* create channel */
    ARGUMENTS(do011), /* create thread */
    ARGUMENTS(do023), /* subscribe to a team */
    ARGUMENTS(do024), /* unsubscribe from a team */
    ARGUMENTS(do025), /* list replies (when in a thread) */
    ARGUMENTS(do026), /* list threads (when in a channel) */
    ARGUMENTS(do027), /* list channels (when in a team) */
    ARGUMENTS(do028), /* list teams (when at the root) */
    ARGUMENTS(do036), /* change user (login when already logged) */
    // Error
    ARGUMENTS(do104), /* unauthorized */
    ARGUMENTS(do105),
    ARGUMENTS(do107),
    ARGUMENTS(do108),
    ARGUMENTS(do109),
};

static const size_t NB_COMMANDS = sizeof(COMMANDS) / sizeof(cmd_t);

/* -- Commands --
/login
/logout
/users


 * -- Commands -- */

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
