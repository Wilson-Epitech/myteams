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

LIB_DIR		=	./libs
LIB_MY_DIR	=	$(LIB_DIR)/my
LIB_NAME	=	$(realpath $(LIB_DIR)/libmy.a)

# -------------------------------------------------------------------------- #


.PHONY: all
all: lib
all: server
all: client


.PHONY: lib
lib: $(LIB_MY_DIR)
	$(MAKE) -c $^ NAME="$(LIB_NAME)" INCLUDE="$(INCLUDE)"


.PHONY: server
server: $(SERVER_DIR)
	$(MAKE) -C $^ INCLUDE="$(INCLUDE)"


.PHONY: client
client: $(CLIENT_DIR)
	$(MAKE) -C $^ INCLUDE="$(INCLUDE)"


.PHONY: clean
clean:
	$(MAKE) -C $(LIB_MY_DIR) clean
	$(MAKE) -C $(SERVER_DIR) clean
	$(MAKE) -C $(CLIENT_DIR) clean


.PHONY: fclean
fclean: clean
	$(MAKE) -C $(LIB_MY_DIR) fclean
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
