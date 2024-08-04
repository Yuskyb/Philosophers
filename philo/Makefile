# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yususato <yususato@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/12 21:36:18 by yususato          #+#    #+#              #
#    Updated: 2024/08/04 16:14:20 by yususato         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc -Wall -Wextra -Werror
INCLUDES_DIR = ./includes
CFLAGS =-I$(INCLUDES_DIR)
SRCS =  philo.c \
		philo_utils_init.c \
		fork_lock.c \
		fork_unlock.c \
		philo_loop.c \
		philo_end_uttils.c \
		philo_utils.c \
		check_argument.c \
		philo_observe.c \
		philo_loop_utils.c \
		ft_atoi.c \
		philo_mutex_utils.c

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re