##
## MYTEAMS PROJECT, 2024
## teams
## File description:
## Makefile
##

# -------------------------------------------------------------------------- #

CC			=	gcc
CPPFLAGS	=	-iquote $(INCLUDE)
CFLAGS		=	-Wall -Wextra -Werror

# -------------------------------------------------------------------------- #

SRC_DIR		=	./src/
NAME		=	../myteams_cli
OBJ			=	$(SRC:.c=.o)
SRC			=	$(SRC_DIR)main.c				\

# -------------------------------------------------------------------------- #

.PHONY: all
all: $(NAME)


$(NAME): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(CPPFLAGS)


.PHONY: clean
clean:
	$(RM) $(OBJ)


.PHONY: fclean
fclean: clean
	$(RM) $(NAME)

# -------------------------------------------------------------------------- #
