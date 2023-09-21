# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: egervais <egervais@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/18 14:49:38 by egervais          #+#    #+#              #
#    Updated: 2023/09/20 20:09:22 by egervais         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= philo
CFLAGS	:= -Wextra -Wall -Werror -g -fsanitize=thread
SRCS	:= main.c

OBJS = ${SRCS:.c=.o}

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re