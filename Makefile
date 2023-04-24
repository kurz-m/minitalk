# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: makurz <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/21 08:46:25 by makurz            #+#    #+#              #
#    Updated: 2023/04/24 06:56:57 by makurz           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Define the names of the executables
NAME := minitalk
SERVERNAME := server
CLIENTNAME := client

# Set compiler and debugger according to OS
UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
	CC := gcc
	DB := gdb
	CFLAGS ?= -Wall -Wextra -Werror -fsanitize=leak
else ifeq ($(UNAME), Darwin)
	CC := cc
	DB := lldb
	CFLAGS ?= -Wall -Wextra -Werror
else
	$(error Unsupported operating system: $(UNAME))
endif

# Define the remove command
RM := rm -f

# Color codes
Y := "\033[33m"
R := "\033[31m"
G := "\033[32m"
X := "\033[0m"
UP := "\033[A"
CUT := "\033[K"

# Name all sources
UTIL := utils.c
SERVERSRC := server.c
CLIENTSRC := client.c

# OBJ from the sources
UTILOBJ := $(UTIL:%.c=%.o)
SERVEROBJ := $(SERVER:%.c=%.o)
CLIENTOBJ := $(CLIENT:%.c=%.o)

all: $(NAME)

$(NAME): $(SERVERNAME) $(CLIENTNAME)

$(SERVERNAME):
	@echo $(Y)Creating [$@]...$(X)
	@$(CC) $(CFLAGS) $(SERVERSRC) $(UTIL) -o $@
	@echo $(G)Finished [$@]$(X)

$(CLIENTNAME):
	@echo $(Y)Creating [$@]...$(X)
	@$(CC) $(CFLAGS) $(CLIENTSRC) $(UTIL) -o $@
	@echo $(G)Finished [$@]$(X)

clean:
	@if [ -f ${CLIENTNAME} ] && [ -f ${SERVERNAME} ]; then \
		echo $(R)Cleaning" "minitalk...$(X); \
		$(RM) ${CLIENTNAME} ${SERVERNAME}; \
		echo $(G)Cleaned!$(X); \
	fi

fclean: clean
	@if [ -f ${NAME} ]; then \
		echo $(R)Cleaning" "minitalk...$(X); \
		$(RM) ${NAME}; \
		echo $(G)Cleaned!$(X); \
	fi

re: fclean all

.PHONY: all clean fclean re
