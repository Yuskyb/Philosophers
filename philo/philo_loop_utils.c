/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_loop_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:13:47 by yususato          #+#    #+#             */
/*   Updated: 2024/08/04 22:55:07 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_stop_flag(t_table_info *table)
{
	pthread_mutex_lock(&table->stop_lock);
	if (table->stop_flag)
	{
		pthread_mutex_unlock(&table->stop_lock);
		return (true);
	}
	pthread_mutex_unlock(&table->stop_lock);
	return (false);
}

bool	check_stop_flag_write(t_table_info *table)
{
	pthread_mutex_lock(&table->stop_lock);
	if (table->stop_flag)
	{
		pthread_mutex_unlock(&table->stop_lock);
		pthread_mutex_unlock(&table->write_lock);
		return (true);
	}
	pthread_mutex_unlock(&table->stop_lock);
	return (false);
}

bool	check_philo_loop_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->stop_lock);
	if (philo->table->stop_flag == true)
	{
		pthread_mutex_unlock(&philo->table->stop_lock);
		pthread_mutex_unlock(&philo->table->write_lock);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (false);
	}
	return (true);
}

void	handle_philo_dead(t_table_info *table, int index)
{
	pthread_mutex_lock(&table->stop_lock);
	table->stop_flag = true;
	pthread_mutex_lock(&table->write_lock);
	printf("%ld %d dead\n", get_current_ms_time() \
		- table->eat_start_time, table->philo[index].id);
	pthread_mutex_unlock(&table->write_lock);
	pthread_mutex_unlock(&table->stop_lock);
	pthread_mutex_unlock(table->philo[index].eat_count_lock);
}

void	handle_full_eat_count(t_table_info *table, int index)
{
	pthread_mutex_lock(&table->stop_lock);
	table->stop_flag = true;
	pthread_mutex_unlock(&table->stop_lock);
	pthread_mutex_unlock(table->philo[index].eat_count_lock);
}
