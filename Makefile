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

.PHONY: all
all: server
all: client


.PHONY: server
server: $(SERVER_DIR)
	$(MAKE) -C $^ INCLUDE="$(INCLUDE)"


.PHONY: client
client: $(CLIENT_DIR)
	$(MAKE) -C $^ INCLUDE="$(INCLUDE)"


.PHONY: clean
clean:
	$(MAKE) -C $(SERVER_DIR) clean
	$(MAKE) -C $(CLIENT_DIR) clean


.PHONY: fclean
fclean: clean
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
