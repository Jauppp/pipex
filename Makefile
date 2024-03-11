# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/07 10:23:52 by cdomet-d          #+#    #+#              #
#    Updated: 2024/03/11 17:49:33 by cdomet-d         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME := pipex
BONUS := pipex_bonus
LIB := libft.a
BUILD_DIR := .dir_build
LIBFT_DIR := libft

CC := cc
CFLAGS := -Werror -Wextra -Wall -g3 
CPPFLAGS = -MMD -MP
MAKEFLAGS += --no-print-directory

SRCS := errors.c \
		init_args.c \
		main.c \
		memory.c \
		utils.c \
		exec_cmd.c \

SRCS_B :=	bonus_errors.c \
			bonus_memory.c \
			bonus_exec_cmd.c \
			bonus_utils.c \
			bonus_main.c \
			bonus_init_args.c \

OBJS := $(addprefix $(BUILD_DIR)/, $(SRCS:%.c=%.o))
OBJS_B := $(addprefix $(BUILD_DIR)/, $(SRCS_B:%.c=%.o))
DEPS := $(OBJS:%.o=%.d)
RM := rm -rf

all: $(NAME)

bonus: $(BONUS)

$(NAME): $(LIBFT_DIR)/$(LIB) $(OBJS)
	@echo
	@echo "$(PURPLE)|========== \t\t Making PIPEX \t\t ===========|$(RESET)"
	@echo
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -o $(NAME) -lft
	@echo
	@echo "$(GREEN)|=========== \t\t PIPEX done ! \t\t ===========|$(RESET)"
	@echo

$(BONUS): $(LIBFT_DIR)/$(LIB) $(OBJS_B)
	@echo
	@echo "$(PURPLE)|========== \t\t Making bonus \t\t ===========|$(RESET)"
	@echo
	$(CC) $(CFLAGS) $(OBJS_B) -L$(LIBFT_DIR) -o $(BONUS) -lft
	@echo
	@echo "$(GREEN)|=========== \t\t Bonus done ! \t\t ===========|$(RESET)"
	@echo

$(BUILD_DIR)/%.o:%.c pipex.h $(LIBFT_DIR)/libft.h Makefile
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $< $(INCLUDES)

$(LIBFT_DIR)/$(LIB): FORCE
	@echo "$(FAINT)"
	$(MAKE) -C $(LIBFT_DIR)
	@echo "$(RESET)"

 -include $(DEPS)
 
clean:
	@echo
	@echo "$(CYAN)|========== \t\t Running clean... \t ===========|$(RESET)"
	@echo "$(FAINT)"
	$(RM) $(BUILD_DIR)
	make -C $(LIBFT_DIR) $@
	@echo "$(RESET)"
	@echo "$(CYAN)|=========== \t\t Done ! \t\t ===========|$(RESET)"
	@echo
	
fclean: clean
	@echo "$(CYAN)|========== \t\t Running fclean... \t ===========|$(RESET)"
	@echo "$(FAINT)"
	make -C $(LIBFT_DIR) $@
	$(RM) $(NAME)
	@echo "$(RESET)"
	@echo "$(CYAN)|========== \t\t Bye <3 \t\t ===========|$(RESET)"
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
BLUE=\033[0;34m
CYAN=\033[0;36m
GREEN=\033[32m
PURPLE=\033[35m
BG_CYAN=\033[46m

# Text
RESET=\033[0m
FAINT=\033[2m
UNDERLINE=\033[4m

FORCE : 
.PHONY : clean fclean all re run help kitty display force bonus