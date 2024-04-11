##
## MYTEAMS PROJECT, 2024
## string
## File description:
## Makefile
##


# -------------------------------------------------------------------------- #

SRC		=	all.c				\
			concat.c			\
			count.c				\
			split.c				\
			add.c		\
			create.c			\

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
