##
## MYTEAMS PROJECT, 2024
## teams
## File description:
## Makefile
##

# -------------------------------------------------------------------------- #

INCLUDE		=	$(realpath ./include/)/

# -------------------------------------------------------------------------- #

SERVER_DIR	=	./server/
CLIENT_DIR	=	./client/

# -------------------------------------------------------------------------- #

LIB_DIR		=	$(realpath ./libs)
LIB_PREFIX	=	my
LIB_MY_DIR	=	$(LIB_DIR)/$(LIB_PREFIX)
LIB_NAME	=	$(realpath ./libs)/libmy.a
LIB_FLAGS	+=	-L $(LIB_DIR)/ -l $(LIB_PREFIX)

# -------------------------------------------------------------------------- #


.PHONY: all
all: lib
	$(MAKE) server
	$(MAKE) client


.PHONY: lib
lib: $(LIB_MY_DIR)
	$(MAKE) -C $^ NAME="$(LIB_NAME)" INCLUDE="$(INCLUDE)"


.PHONY: server
server: $(SERVER_DIR)
	$(MAKE) -C $^ INCLUDE="$(INCLUDE)" LIB="$(LIB_FLAGS)"


.PHONY: client
client: $(CLIENT_DIR)
	$(MAKE) -C $^ INCLUDE="$(INCLUDE)" LIB="$(LIB_FLAGS)"


.PHONY: clean
clean:
	$(MAKE) -C $(LIB_MY_DIR) clean
	$(MAKE) -C $(SERVER_DIR) clean
	$(MAKE) -C $(CLIENT_DIR) clean
	$(RM) vgcore*


.PHONY: fclean
fclean: clean
	$(MAKE) -C $(LIB_MY_DIR) fclean NAME="$(LIB_NAME)"
	$(MAKE) -C $(SERVER_DIR) fclean
	$(MAKE) -C $(CLIENT_DIR) fclean


.PHONY: re
re: fclean
	$(MAKE) all


.PHONY: tests_run
tests_run:


.PHONY: test
test:

# -------------------------------------------------------------------------- #
