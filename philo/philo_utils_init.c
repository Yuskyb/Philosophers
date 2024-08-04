/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:40:06 by yususato          #+#    #+#             */
/*   Updated: 2024/08/04 17:18:49 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	thread_init(t_table_info *table_tmp, t_philo *philo_tmp \
						, int philo_count)
{
	int	index;

	index = 0;
	while (index < table_tmp->philo_count)
	{
		philo_tmp[index].table = table_tmp;
		index++;
	}
	index = 0;
	table_tmp->philo = philo_tmp;
	table_tmp->eat_start_time = get_current_ms_time() + 10;
	while (index < philo_count)
	{
		if (pthread_create(&philo_tmp[index].thread, NULL
				, philo_loop, &philo_tmp[index]) != 0)
		{
			return (table_tmp->create_count = index, false);
		}
		index++;
	}
	if (pthread_create(&(table_tmp->supervisor), NULL \
							, supervisor_loop, table_tmp) != 0)
		return (table_tmp->create_count = -1, false);
	return (table_tmp->create_count = index, true);
}

bool	fork_eat_mutex_init(pthread_mutex_t *fork \
		, pthread_mutex_t *full_eat_flag_lock \
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
		if (pthread_mutex_init(&full_eat_flag_lock[index], NULL) != 0)
			return (false);
		index++;
	}
	return (true);
}

void	fork_eat_mutex_insert(t_philo *philo \
		, pthread_mutex_t *fork, pthread_mutex_t *full_eat_flag_lock \
		, pthread_mutex_t *eat_count_lock)
{
	int	index;

	index = 0;
	while (index < philo->table->philo_count)
	{
		philo[index].eat_count_lock = &eat_count_lock[index];
		philo[index].full_eat_flag_lock = &full_eat_flag_lock[index];
		philo[index].left_fork = &fork[index];
		if (index + 1 == philo->table->philo_count)
			philo[index].right_fork = &fork[0];
		else
			philo[index].right_fork = &fork[index + 1];
		index++;
	}
}

bool	fork_eat_init(t_philo *philo, int philo_count)
{
	pthread_mutex_t	*fork;
	pthread_mutex_t	*eat_count_lock;
	pthread_mutex_t	*full_eat_flag_lock;

	eat_count_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
						* philo_count);
	if (eat_count_lock == NULL)
		return (false);
	full_eat_flag_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
						* philo_count);
	if (full_eat_flag_lock == NULL)
		return (false);
	fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * philo_count);
	if (fork == NULL)
		return (free(eat_count_lock), false);
	if (fork_eat_mutex_init(fork, full_eat_flag_lock \
		, eat_count_lock, philo_count) == false)
		return (ft_free_table(philo->table), false);
	fork_eat_mutex_insert(philo, fork, full_eat_flag_lock \
		, eat_count_lock);
	return (true);
}

bool	table_philo_mutex_init(t_table_info *table \
		, t_philo *philo, int philo_count)
{
	pthread_mutex_t	stop_lock_tmp;
	pthread_mutex_t	write_lock_tmp;

	if (fork_eat_init(philo, philo_count) == false)
	{
		free(table);
		free(philo);
		return (false);
	}
	if (pthread_mutex_init(&(stop_lock_tmp), NULL) != 0)
	{
		ft_free_table(table);
		return (false);
	}
	if (pthread_mutex_init(&(write_lock_tmp), NULL) != 0)
	{
		ft_free_table(table);
		return (false);
	}
	table->stop_lock = stop_lock_tmp;
	table->write_lock = write_lock_tmp;
	return (true);
}
