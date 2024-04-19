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
NAME		=	../myteams_cli
OBJ			=	$(SRC:.c=.o)
SRC			=	$(SRC_DIR)main.c				\
				$(SRC_DIR)client.c				\
				$(SRC_DIR)dolib.c				\
				$(SRC_DIR)douser.c				\
				$(SRC_DIR)dosend.c				\

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
