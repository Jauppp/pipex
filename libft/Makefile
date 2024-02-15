# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/07 10:23:52 by cdomet-d          #+#    #+#              #
#    Updated: 2024/01/19 16:15:57 by cdomet-d         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc
CFLAGS = -Werror -Wextra -Wall
CPPFLAGS = -MMD -MP

BUILD_DIR := .dir_build
SRCS := ft_atoi.c \
		ft_atoi_intmax.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_itoa.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putstr_fd.c \
		ft_split.c \
		ft_strchr.c \
		ft_strdup.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strmapi.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strtrim.c \
		ft_substr.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_putnbrs.c \
		ft_printf.c \
		ft_print_chars.c \
		ft_print_nums.c \
		ft_lstadd_back.c \
		ft_lstclear.c \
		ft_lstdelone.c \
		ft_lstiter.c \
		ft_lstnew.c \
		ft_lstmap.c \
 		ft_lstadd_front.c \
 		ft_lstlast.c \
 		ft_lstsize.c \
		get_next_line.c \
		get_next_line_utils.c \
		ft_isspace.c \
		ft_isdigit_negative.c \
		ft_lstfree.c \
		
OBJS := $(SRCS:%.c=$(BUILD_DIR)/%.o)
				
DEPS := $(OBJS:%.o=%.d)
RM := rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	@echo
	@echo "$(PURPLE)|=========== \t\t Creating libft.a... \t\t ===========|$(BLACK)"
	@echo
	ar -rcs $(NAME) $(OBJS)
	@echo
	@echo "$(GREEN)|=========== \t\t libft.a done ! \t\t ===========|$(BLACK)"
	@echo

$(BUILD_DIR)/%.o:%.c libft.h
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

 -include $(DEPS)

clean: 
	$(RM) $(BUILD_DIR)
fclean: clean
	$(RM) $(NAME)
re: fclean all

# Colors
BLACK=\033[30m
GREEN=\033[32m
PURPLE=\033[35m

.PHONY : clean fclean all re BLACK PURPLE GREEN