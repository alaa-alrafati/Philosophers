# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aalrofat <aalrofat@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/04 12:44:48 by aalrofat          #+#    #+#              #
#    Updated: 2026/03/04 12:44:48 by aalrofat         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc 
CFLAGS = -Wall -Wextra -Werror
SRC = philo.c  init_mutex_philo.c create_threads.c utils_philo_process.c monitor_process.c utils.c
OBJ = $(SRC:.c=.o)
NAME = philo

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -pthread -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
