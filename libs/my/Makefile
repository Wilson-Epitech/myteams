##
## MYTEAMS PROJECT, 2024
## teams
## File description:
## Makefile
##

# -------------------------------------------------------------------------- #

CPPFLAGS	=	-iquote $(INCLUDE)

# -------------------------------------------------------------------------- #

LIBS	=	arr			\
			mem			\
			str			\
			file		\

# -------------------------------------------------------------------------- #

.PHONY: all
all:
	for lib in $(LIBS);\
	do $(MAKE) -C $$lib NAME="$(NAME)" CPPFLAGS="$(CPPFLAGS)"; done


.PHONY: clean
clean:
	for lib in $(LIBS); do $(MAKE) -C $$lib clean; done


.PHONY: fclean
fclean: clean
	$(RM) $(NAME)


.PHONY: re
re: fclean
	$(MAKE) all

# -------------------------------------------------------------------------- #
