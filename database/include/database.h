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

//--------save commands -------//
int save_users(user_t **users);
int save_reply(reply_t **reply);
int save_threads(thread_t **thread);

//--------create commands -------//
int create_file(char *file);


int build_database(void);

#endif /* !DATABASE_H_ */
