/*
** MYTEAMS PROJECT, 2024
** myteams
** File description:
** database
*/

#ifndef DATABASE_H_
    #define DATABASE_H_

typedef struct db_s {
} db_t;

int save_users(user_t **users);
int create_file(char *file);
int build_database(void);

#endif /* !DATABASE_H_ */
