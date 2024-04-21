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
NAME		=	../myteams_cli
OBJ			=	$(SRC:.c=.o)
SRC			=	$(SRC_DIR)main.c				\
				$(SRC_DIR)client.c				\
				$(SRC_DIR)dolib.c				\
				$(SRC_DIR)dolib2.c				\
				$(SRC_DIR)dolib3.c				\
				$(SRC_DIR)dolib4.c				\
				$(SRC_DIR)dolib5.c				\
				$(SRC_DIR)dolib6.c				\

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
