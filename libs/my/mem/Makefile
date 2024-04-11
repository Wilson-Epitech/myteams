##
## MYTEAMS PROJECT, 2024
## string
## File description:
## Makefile
##


# -------------------------------------------------------------------------- #

SRC		=	alloc.c				\
			auto_free.c			\
			constructor.c		\
			destroy.c			\
			destructor.c		\
			setget.c			\
			try_free.c			\
			ptrlen.c			\
			alloc_resize.c		\

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
