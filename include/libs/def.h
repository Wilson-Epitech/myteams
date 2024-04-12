/*
** MYTEAMS PROJECT, 2024
** my-ftp
** File description:
** def
*/

#pragma once

// Return Status
#define FAILURE 84
#define SUCCESS 0

// Perror Prefix (For myTeams, we cannot print errors on stderr)
#define PERR(x) (FAILURE + 0 * printf("ERROR: " x "\n"))
#define PERR_NORET(x) printf("ERROR: " x "\n")

// Unused Variable / Function
#define UNUSED __attribute__((unused))
