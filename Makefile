# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/07 10:23:52 by cdomet-d          #+#    #+#              #
#    Updated: 2024/03/01 16:43:56 by cdomet-d         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME := pipex
LIB := libft.a
BUILD_DIR := .dir_build
LIBFT_DIR := libft

CC := cc
CFLAGS := -Werror -Wextra -Wall -g3 
CPPFLAGS = -MMD -MP
MAKEFLAGS += --no-print-directory

SRCS := display.c \
		errors.c \
		init_args.c \
		main.c \
		memory.c \
		utils.c \
		exec_cmd.c \

OBJS := $(addprefix $(BUILD_DIR)/, $(SRCS:%.c=%.o))
DEPS := $(OBJS:%.o=%.d)
RM := rm -rf

all: $(NAME) clout

$(NAME): $(LIBFT_DIR)/$(LIB) $(OBJS)
	@echo
	@echo "$(PURPLE)|========== \t\t Making PIPEX \t\t ===========|$(BLACK)"
	@echo
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -o $(NAME) -lft
	@echo
	@echo "$(GREEN)|=========== \t\t PIPEX done ! \t\t ===========|$(BLACK)"
	@echo

$(BUILD_DIR)/%.o:%.c pipex.h $(LIBFT_DIR)/libft.h Makefile
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $< $(INCLUDES)

$(LIBFT_DIR)/$(LIB): FORCE
	@echo "$(FAINT)"
	$(MAKE) -C $(LIBFT_DIR)
	@echo "$(RESET)"

 -include $(DEPS)

clout:
	@rm -f out
	@rm -f outfile
	@rm -f outsh
	@rm -f oush

clean:
	@echo "$(FAINT)"
	@echo
	@echo "$(PURPLE)|========== \t\t Cleaning... \t\t ===========|$(BLACK)"
	@echo
	$(RM) $(BUILD_DIR)
	make -C $(LIBFT_DIR) $@

fclean: clean
	@echo "$(FAINT)"
	make -C $(LIBFT_DIR) $@
	$(RM) $(NAME)
	@echo
	@echo "$(PURPLE)|========== \t\t Bye <3 \t\t ===========|$(BLACK)"
	@echo

re: fclean all

run: all
	@./$(NAME)

valgrind: all
	@valgrind --leak-check=full ./$(NAME)

help:
	@echo "make \t\t $(FAINT)makes executable$(RESET)"
	@echo "make clean \t $(FAINT)deletes object files & dependencies$(RESET)"
	@echo "make fclean \t $(FAINT)deletes everything the makefile created$(RESET)"
	@echo "make kitty \t $(FAINT)prints a lil kitty on the terminal$(RESET)"
	@echo "make re \t $(FAINT)deletes all objects & dependencies and recompiles everything$(RESET)"

kitty:
	@echo "   |\__/,|   ( \  "
	@echo " _.|o o  |_   ) ) "
	@echo "-(((---(((--------"

# Colors
BLACK=\033[30m
GREEN=\033[32m
PURPLE=\033[35m

# Text
RESET=\033[0m
FAINT=\033[2m
UNDERLINE=\033[4m

FORCE : 
.PHONY : clean fclean all re run help kitty display force bonus