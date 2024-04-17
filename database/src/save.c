/*
** MYTEAMS PROJECT, 2024
** myteams
** File description:
** save
*/

static int is_file(const char *filepath)
{
    struct stat file;

    if (stat(filepath, &file) == 0 && S_ISREG(file.st_mode))
        return 1;
    return 0;
}

int save_user(user_t **users)
{
    int fd = 0;
    char *path = getcwd(NULL, 0);

    strcat(path, "/data/users.txt");
    if (is_file(path) == 0)
        create_file("data/users.txt");
    fd = open(path, O_RDWR | O_APPEND, 0644);
    if (fd == -1) {
        PERR_NORET("Open failed");
        return 84;
    }
    for (int i = 0; users[i] != NULL; i++) {
        dprintf(fd, "%s %s\n", users[i].uuid, users[i].name)
    }
    close(fd);
    return 0;
}