# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: imane <imane@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/27 01:06:33 by imane             #+#    #+#              #
#    Updated: 2022/08/30 13:00:42 by imane            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo_bonus
SRC		= philo_bonus.c processes_bonus.c functions_bonus.c checkers_bonus.c
CC		= gcc #-g -fsanitize=thread
# CFLAGS	= -Wall -Wextra -Werror
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