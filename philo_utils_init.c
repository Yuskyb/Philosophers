/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:40:06 by yususato          #+#    #+#             */
/*   Updated: 2024/07/16 13:40:38 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*philo_init(int count_tmp, int dead_tmp, int eat_tmp, int sleep_tmp, int goal_tmp)
{
	t_philo	*philo;
	int		index;

	index = 0;
	philo = (t_philo *)malloc(sizeof(t_philo) * count_tmp);
	if (philo == NULL)
		return (NULL);
	while (index < count_tmp)
	{
		philo[index].id = index;
		philo[index].dead_time = dead_tmp;
		philo[index].eat_time = eat_tmp;
		philo[index].sleep_time = sleep_tmp;
		philo[index].eat_count = 0;
		philo[index].eat_count_goal = goal_tmp;
		index++;
	}
	return (philo);
}

void	thread_init(t_philo *philo, int philo_count)
{
	pthread_t	*thread_index;
	int			index;

	index = 0;
	thread_index = (pthread_t *)malloc(sizeof(pthread_t) * philo_count);
	if (thread_index == NULL)
		exit(0);
	while (index < philo_count)
	{
		philo[index].thread = thread_index[index];
		index++;
	}
	return ;
}

void	fork_init(t_philo *philo, int philo_count)
{
	int				index;
	t_mutex_thread	*fork;

	index = 0;
	fork = (t_mutex_thread *)malloc(sizeof(t_mutex_thread) * philo_count);
	if (fork == NULL)
		exit(0);
	while (index < philo_count)
	{
		philo[index].left_fork = fork[index];
		if (index + 1 == philo_count)
			philo[index].right_fork = fork[0];
		else
			philo[index].right_fork = fork[index + 1];
		index++;
	}
	return ;
}
