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

bool	thread_init(t_table_info *table_tmp, t_philo *philo_tmp, int philo_count)
{
	int			index;

	index = 0;
	while (index < philo_count)
	{
		philo_tmp[index].table = table_tmp;
		index++;
	}
	table_tmp->philo = philo_tmp;
	index = 0;
	table_tmp->eat_start_time = get_current_ms_time();
	while (index < philo_count)
	{
		if (pthread_create(&philo_tmp[index].thread, NULL
			, philo_loop, &philo_tmp[index]) != 0)
			return (false);
		index++;
	}
	pthread_create(&(table_tmp->supervisor), NULL, supervisor_loop, table_tmp);
	return (true);
}

bool	fork_eat_mutex_init(pthread_mutex_t *fork \
		, pthread_mutex_t *eat_count_lock, int philo_count)
{
	int	index;

	index = 0;
	while (index < philo_count)
	{
		if (pthread_mutex_init(&fork[index], NULL) != 0)
			return (false);
		if (pthread_mutex_init(&eat_count_lock[index], NULL) != 0)
			return (false);
		index++;
	}
	return (true);
}

bool	fork_eat_init(t_philo *philo, int philo_count)
{
	int				index;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*eat_count_lock;

	index = 0;
	eat_count_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * philo_count);
	fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * philo_count);
	if (eat_count_lock == NULL || fork == NULL)
		return (false);
	fork_eat_mutex_init(fork, eat_count_lock, philo_count);
	while (index < philo_count)
	{
		philo[index].eat_count_lock = &eat_count_lock[index];
		philo[index].left_fork = &fork[index];
		if (index + 1 == philo_count)
			philo[index].right_fork = &fork[0];
		else
			philo[index].right_fork = &fork[index + 1];
		index++;
	}
	return (true);
}

bool	table_philo_mutex_init(t_table_info *table \
		, t_philo *philo, int philo_count)
{
	pthread_mutex_t	stop_lock_tmp;
	pthread_mutex_t	write_lock_tmp;

	if (fork_eat_init(philo, philo_count) == false)
		return (false);
	if (pthread_mutex_init(&(stop_lock_tmp), NULL) != 0)
		return (false);
	if (pthread_mutex_init(&(write_lock_tmp), NULL) != 0)
		return (false);
	table->stop_lock = stop_lock_tmp;
	table->write_lock = write_lock_tmp;
	return (true);
}
