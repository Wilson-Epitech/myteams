##
## MYTEAMS PROJECT, 2024
## teams
## File description:
## Makefile
##

# -------------------------------------------------------------------------- #

CC			=	gcc
CPPFLAGS	=	-iquote $(INCLUDE) -iquote ./include/
CFLAGS		=	-Wall -Wextra -Werror -g3

# -------------------------------------------------------------------------- #

SRC_DIR		=	./src/
NAME		=	../myteams_server
OBJ			=	$(SRC:.c=.o)
SRC			=	$(SRC_DIR)server.c				\
				$(SRC_DIR)mem1.c				\
				$(SRC_DIR)mem2.c				\
				$(SRC_DIR)mem3.c				\
				$(SRC_DIR)mem4.c				\
				$(SRC_DIR)init_server.c			\
				$(SRC_DIR)run_server.c			\
				$(SRC_DIR)cmd_handler.c			\
				$(SRC_DIR)utils1.c				\
				$(SRC_DIR)utils2.c				\
				$(CMD)							\
				$(DB)							\

CMD_DIR		=	$(SRC_DIR)cmd/
CMD			=	$(CMD_DIR)login.c				\
				$(CMD_DIR)logout.c				\
				$(CMD_DIR)help.c				\
				$(CMD_DIR)users.c				\
				$(CMD_DIR)user.c				\
				$(CMD_DIR)create.c				\
				$(CMD_DIR)use.c					\
				$(CMD_DIR)subscribed.c			\
				$(CMD_DIR)subscribe.c			\
				$(CMD_DIR)unsubscribe.c			\
				$(CMD_DIR)list.c				\
				$(CMD_DIR)info.c				\
				$(CMD_DIR)send.c				\
				$(CMD_DIR)messages.c			\

DB_DIR		=	./src/database/
DB			=	$(DB_DIR)save_db.c				\

# -------------------------------------------------------------------------- #

.PHONY: all
all: $(NAME)


$(NAME): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(CPPFLAGS) $(LIB)


.PHONY: clean
clean:
	$(RM) $(OBJ)


.PHONY: fclean
fclean: clean
	$(RM) $(NAME)

# -------------------------------------------------------------------------- #
