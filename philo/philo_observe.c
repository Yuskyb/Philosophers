/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_observe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 11:54:54 by yususato          #+#    #+#             */
/*   Updated: 2024/08/04 22:30:18 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_full_eat_count(t_table_info *table)
{
	int	index;
	int	count;

	index = 0;
	count = 0;
	while (index < table->philo_count)
	{
		if (observe_full_eat_flag(&table->philo[index]) == true)
			count++;
		index++;
	}
	if (count == table->philo_count)
		return (true);
	return (false);
}

bool	check_dead_philo(t_philo *philo)
{
	if (!philo->last_eat_time)
		philo->last_eat_time = philo->table->eat_start_time;
	if (get_current_ms_time() - philo->last_eat_time \
		> philo->table->dead_time)
	{
		philo->dead_flag = true;
		return (true);
	}
	return (false);
}

bool	check_dead(t_philo *philo, int index)
{
	if (check_dead_philo(&philo[index]))
		return (true);
	return (false);
}

void	*supervisor_loop(void *argc)
{
	int				index;
	t_table_info	*table;

	table = (t_table_info *)argc;
	if (table->philo_count == 1)
		return (NULL);
	wait_start_dinner_time(table);
	while (true)
	{
		index = 0;
		if (check_stop_flag(table) == true)
			return (NULL);
		while (index < table->philo_count)
		{
			pthread_mutex_lock(table->philo[index].eat_count_lock);
			if (check_dead(table->philo, index))
				return (handle_philo_dead(table, index), NULL);
			if (table->eat_count_goal_flag == true \
				&& check_full_eat_count(table))
				return (handle_full_eat_count(table, index), NULL);
			pthread_mutex_unlock(table->philo[index].eat_count_lock);
			index++;
		}
	}
	return (NULL);
}
