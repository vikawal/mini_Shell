# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ovolzhev <ovolzhev@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/05 20:05:46 by ovolzhev          #+#    #+#              #
#    Updated: 2024/08/24 16:16:28 by ovolzhev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = hell.c \
	lib1/ft_bzero.c \
	lib1/ft_calloc.c \
	lib1/ft_isdigit.c\
	lib1/ft_itoa.c \
	lib1/ft_split.c \
	lib1/ft_strchr.c \
	lib1/ft_strjoin.c \
	lib1/ft_strlcpy.c \
	lib1/ft_strlen.c \
	lib1/ft_strncmp.c \
	lib1/ft_strtrim.c \
	lib1/ft_substr.c \
	lib1/search.c \
	utils/free_the_hell.c \
	utils/init_hell.c \
	utils/space_putter.c \
	utils/fill_hell.c \
	utils/errors.c \
	utils/makefds.c \
	utils/heredoc_stuff.c \
	utils/create_env.c \
	utils/dollar.c \
	utils/utils_to_fill.c \
	lib1/ft_strdup.c \
	lib1/ft_putstr_fd.c \
	lib1/ft_putchar_fd.c \
	lib1/ft_putendl_fd.c \
	lib1/ft_strnstr.c \
	build/execute/linked_list.c \
	build/execute/2_linked_list.c \
	build/execute/more_utils.c \
	build/execute/2_more_utils.c \
	build/execute/new_build.c \
	build/execute/env.c \
	build/execute/built_in_check.c \
	build/execute/new_export.c \
	build/execute/new_cd.c \
	build/execute/check_path.c \
	build/execute/executing_2.c \
	build/execute/executing.c \
	build/execute/new_echo.c \
	build/execute/new_unset.c \
	build/execute/libft_utils.c
	
HEADERS = hell.h lib1/libft.h

OBJS = $(SRC:.c=.o)

CC = cc

CFLAGS = -g -Wall -Wextra -Werror

all: $(NAME) $(HEADERS)

$(NAME): $(OBJS)
	@ $(CC) $(CFLAGS) -o $(NAME) $^ -lreadline -lc
	@echo DONE CREATING

%.o: %.c $(HEADERS)
	@ $(CC) $(CFLAGS) -c -o $@ $<

clean:
	@rm -f *.o
	@rm -f utils/*.o
	@rm -f build/execute/*.o
	@rm -f lib1/*.o
	@echo DONE DELETING

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean re fclean