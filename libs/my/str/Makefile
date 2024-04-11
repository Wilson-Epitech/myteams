##
## MYTEAMS PROJECT, 2024
## string
## File description:
## Makefile
##


# -------------------------------------------------------------------------- #

SRC		=	str_all.c		\
			str_concat.c	\
			str_count.c		\
			str_add.c		\
			str_create.c	\
			split.c			\

OBJ		=	$(SRC:.c=.o)

# -------------------------------------------------------------------------- #

.PHONY: all
all: $(NAME)


$(NAME): $(OBJ)
	$(AR) rc $@ $^


.PHONY: clean
clean:
	$(RM) $(OBJ)

# -------------------------------------------------------------------------- #
