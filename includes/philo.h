/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:33:45 by yususato          #+#    #+#             */
/*   Updated: 2024/07/12 22:14:14 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <limits.h>
# include <string.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				dead_time;
	int				eat_time;
	int				sleep_time;
	int				eat_count;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	right_fork;
	int				eat_count_goal;
} t_philo;

t_philo	*philo_init(int count_tmp, int dead_tmp, \
			int eat_tmp, int sleep_tmp, int goal_tmp);
void	fork_init(t_philo *philo, int philo_count);

#endif