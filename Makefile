# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: makurz <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/21 08:46:25 by makurz            #+#    #+#              #
#    Updated: 2023/04/24 09:41:25 by makurz           ###   ########.fr        #
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

# Name all sources
UTILSRC := utils.c
SERVERSRC := server.c
CLIENTSRC := client.c

# OBJ from the sources
UTILOBJ := $(UTILSRC:%.c=%.o)
SERVEROBJ := $(SERVERSRC:%.c=%.o)
CLIENTOBJ := $(CLIENTSRC:%.c=%.o)

all: $(NAME)

$(NAME): $(SERVERNAME) $(CLIENTNAME)

$(SERVERNAME): $(SERVEROBJ) $(UTILOBJ)
	@echo $(Y)Creating [$@]...$(X)
	@$(CC) $(SERVEROBJ) $(UTILOBJ) -o $@
	@echo $(G)Finished [$@]$(X)

$(CLIENTNAME): $(CLIENTOBJ) $(UTILOBJ)
	@echo $(Y)Creating [$@]...$(X)
	@$(CC) $(CLIENTOBJ) $(UTILOBJ) -o $@
	@echo $(G)Finished [$@]$(X)

# Create static rule for compiling the objectfiles
%.o: %.c
	@$(CC) -c $(CFLAGS) $< -o $@

# Create rule for cleaning the object files
clean:
	@if [ -f ${CLIENTOBJ} ] && [ -f ${SERVEROBJ} ]; then \
		echo $(R)Cleaning" "objects...$(X); \
		$(RM) ${CLIENTOBJ} ${SERVEROBJ} ${UTILOBJ}; \
		echo $(G)Cleaned!$(X); \
	fi

# Create rule for cleaning also the executables
fclean: clean
	@if [ -f ${CLIENTNAME} ] && [ -f ${SERVERNAME} ]; then \
		echo $(R)Cleaning" "minitalk...$(X); \
		$(RM) ${CLIENTNAME} ${SERVERNAME}; \
		echo $(G)Cleaned!$(X); \
	fi

re: fclean all

.PHONY: all clean fclean re
