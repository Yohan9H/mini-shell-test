# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apernot <apernot@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/01 11:27:53 by yohurteb          #+#    #+#              #
#    Updated: 2024/09/30 14:58:09 by apernot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc -Wall -Werror -Wextra

CFLAGS =  -I include/

LDFLAGS = -lreadline

SRCS = \
	src/main.c \
	src/init.c \
	src/signals/signals.c \
	src/env/create_linked_env.c \
	src/lexer/lexer.c \
	src/lexer/handle_space.c \
	src/lexer/meta_char.c \
	src/lexer/meta_char_two.c \
	src/lexer/meta_char_three.c \
	src/lexer/dollar_in_dq.c \
	src/lexer/dollar_in_dq_two.c \
	src/lexer/utils_lexer/utils_lxr.c \
	src/lexer/utils_lexer/utils_lxr_two.c \
	src/parser/parser.c \
	src/parser/state.c \
	src/parser/verif_state.c \
	src/parser/linked_exc.c \
	src/parser/linked_exc_two.c \
	src/parser/utils_parser/utils_parser.c \
	src/exec/exec.c \
	src/exec/exec_utils.c \
	src/exec/exec_utils2.c \
	src/exec/child.c \
	src/exec/parsing_com.c \
	src/exec/verif_builtin.c \
	src/exec/builtin.c \
	src/exec/builtin_two.c \
	src/exec/builtin_three.c \
	src/exec/builtin_four.c \
	utils/garbage_collector.c \
	utils/ft_split.c \
	utils/ft_strlen.c \
	utils/ft_lstadd_back.c \
	utils/ft_lstadd_front.c \
	utils/ft_lstclear.c \
	utils/ft_lstlast.c \
	utils/ft_lstnew.c \
	utils/ft_strncmp.c \
	utils/ft_strdup.c \
	utils/ft_strjoin.c \
	utils/fts_lst.c \
	utils/give_value_env.c \
	utils/ft_isprint.c \
	utils/ft_putstr_fd.c \
	utils/ft_itoa.c \
	utils/ft_atoi.c \
	utils/ft_lstsize.c \
	utils/ft_fprintf.c \
	utils/ft_fprintf_utils.c \
	utils/ft_substr.c \
	utils/ft_freetab.c \
	utils/ft_isnum.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
