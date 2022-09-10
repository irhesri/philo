# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: imane <imane@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/27 01:06:33 by imane             #+#    #+#              #
#    Updated: 2022/09/10 10:22:30 by imane            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo_bonus
SRC		= philo_bonus.c processes_bonus.c functions_bonus.c checkers_bonus.c sem_name.c
CC		= gcc -g #-fsanitize=address
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