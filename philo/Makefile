# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: irhesri <irhesri@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/27 01:06:47 by imane             #+#    #+#              #
#    Updated: 2022/08/27 05:24:59 by irhesri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo
SRC		= functions.c  init.c  philo.c
CC		= gcc #-g -fsanitize=thread
CFLAGS	= -Wall -Wextra -Werror
OBJ		= $(SRC:%.c=%.o)

all: $(NAME)

$(NAME) : $(OBJ)
	@$(CC) $^ -o $@

%.o : %.c 
	@gcc $(CFLAGS) -o $@ -c $<

clean:
	@rm -rf *.o

fclean: clean
	@rm -rf $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re