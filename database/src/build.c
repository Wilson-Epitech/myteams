/*
** MYTEAMS PROJECT, 2024
** myteams
** File description:
** build
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <ctype.h>

#include "../../include/libs/def.h"

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

static char *update_path(char *current_path, char *dirname)
{
    char *new_path = NULL;

    new_path = strdup(current_path);
    strcat(new_path, "/");
    strcat(new_path, dirname);
    return new_path;
}

static char *get_filename_from_path(char *path)
{
    char *filename = strrchr(path, '/');

    if (filename != NULL) {
        filename[1] = toupper(filename[1]);
        return filename + 1;
    }
    return NULL;
}

// Impossible de creer le directory, voir pour les messages avec Marius si
// il faut l'ecrire sur la sortis d'erreur ou non.
static int create_directory(char *dirname)
{
    char *path = update_path(getcwd(NULL, 0), dirname);

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

    if (strlen(filename) % 2 != 0)
        nb = 1;
    strcat(str, "║");
    for (int i = 0; i < (spaces_count / 2); i++) {
        strcat(str, " ");
    }
    strcat(str, filename);
    for (int i = 0; i < (spaces_count / 2) + nb; i++) {
        strcat(str, " ");
    }
    strcat(str, "║\n");
    return str;
}

static char **create_header_file(char *filepath)
{
    size_t max_len = 60;
    char *filename = get_filename_from_path(filepath);
    int spaces_count = (max_len - 6) - strlen(filename);
    char **header = malloc(sizeof(char *) * 4);

    header[0] =
        strdup("╔══════════════════════════════════════════════════════╗\n");
    header[1] = create_second_line(filename, spaces_count);
    header[2] =
        strdup("╚══════════════════════════════════════════════════════╝\n");
    header[3] = NULL;
    return header;
}

// Impossible de creer le fichier, voir pour les messages avec Marius si il
// faut l'ecrire sur la sortis d'erreur ou non.
static int create_file(char *file)
{
    char *path = update_path(getcwd(NULL, 0), file);
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
int main(void)
{
    create_directory("data");
    create_directory("data/messages");
    create_file("data/users.txt");
    create_file("data/teams.txt");
    create_file("data/channels.txt");
    create_file("data/threads.txt");
}
