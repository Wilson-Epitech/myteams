/*
** MYTEAMS PROJECT, 2024
** myteams
** File description:
** build
*/

#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "libs/def.h"

static int is_dir(const char *filepath)
{
    struct stat file;

    if (stat(filepath, &file) == 0 && S_ISDIR(file.st_mode))
        return 1;
    return 0;
}

static int is_file(const char *filepath)
{
    struct stat file;

    if (stat(filepath, &file) == 0 && S_ISREG(file.st_mode))
        return 1;
    return 0;
}

static char *get_filename_from_path(char *path)
{
    char *filename = strrchr(path, '/');

    if (filename != NULL) {
        return filename + 1;
    }
    return NULL;
}

static int create_directory(char *path)
{
    if (is_dir(path) == 0) {
        if (mkdir(path, 0755) != 0) {
            PERR_NORET("Mkdir failed");
            return 84;
        }
    }
    return 0;
}

static char *create_second_line(char *filename, int spaces_count)
{
    char *str = malloc(sizeof(char) * 60);
    int nb = 0;

    *str = '\0';
    if (strlen(filename) % 2 != 0)
        nb = 1;
    strcat(str, "#");
    for (int i = 0; i < (spaces_count / 2); i++) {
        strcat(str, " ");
    }
    strcat(str, filename);
    for (int i = 0; i < (spaces_count / 2) + nb; i++) {
        strcat(str, " ");
    }
    strcat(str, "#\n");
    return str;
}

static char **create_header_file(char *filepath)
{
    size_t max_len = 60;
    char *filename = get_filename_from_path(filepath);
    int spaces_count = (max_len - 6) - strlen(filename);
    char **header = malloc(sizeof(char *) * 4);

    header[0] =
    strdup("########################################################\n");
    header[1] = create_second_line(filename, spaces_count);
    header[2] =
    strdup("########################################################\n\n");
    header[3] = NULL;
    return header;
}

int create_file(char *path)
{
    char **header = NULL;
    int fd = 0;

    if (is_file(path) == 0) {
        fd = open(path, O_RDWR | O_CREAT, 0644);
        if (fd == -1) {
            PERR_NORET("Open failed");
            return 84;
        }
        header = create_header_file(path);
        for (int i = 0; header[i] != NULL; i++) {
            write(fd, header[i], strlen(header[i]));
        }
        close(fd);
    }
    return 0;
}

// database loop pour verifier que tous les fichier sont créer
int build_database(void)
{
    if (create_directory("./database/data") == 84)
        return 84;
    if (create_directory("./database/data/messages") == 84)
        return 84;
    if (create_file("./database/data/users.txt") == 84)
        return 84;
    if (create_file("./database/data/teams.txt") == 84)
        return 84;
    if (create_file("./database/data/channels.txt") == 84)
        return 84;
    if (create_file("./database/data/threads.txt") == 84)
        return 84;
    return 0;
}
