# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/01 11:27:53 by yohurteb          #+#    #+#              #
#    Updated: 2024/09/02 12:16:09 by yohurteb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

CFLAGS = -Wall -Werror -Wextra -I include/ -g

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
	test/test.c # ---- POUR TEST A ENLEVER ----

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