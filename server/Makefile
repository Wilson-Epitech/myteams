##
## MYTEAMS PROJECT, 2024
## teams
## File description:
## Makefile
##

# -------------------------------------------------------------------------- #

CC			=	gcc
CPPFLAGS	=	-iquote $(INCLUDE) -iquote ./include/
CFLAGS		=	-Wall -Wextra -Werror

# -------------------------------------------------------------------------- #

SRC_DIR		=	./src/
NAME		=	../myteams_server
OBJ			=	$(SRC:.c=.o)
SRC			=	$(SRC_DIR)main.c				\
				$(SRC_DIR)mem.c					\
				$(SRC_DIR)init_server.c			\
				$(SRC_DIR)run_server.c			\
				$(SRC_DIR)reply.c				\
				$(SRC_DIR)cmd_handler.c			\

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
