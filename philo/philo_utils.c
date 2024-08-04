/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 11:54:58 by yususato          #+#    #+#             */
/*   Updated: 2024/08/04 17:19:07 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_start_dinner_time(t_table_info *table)
{
	while (table->eat_start_time > get_current_ms_time())
		continue ;
}

long	get_current_ms_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_free_table(t_table_info *table)
{
	int		index;

	index = 0;
	if (table == NULL)
		return ;
	free(table->philo[index].left_fork);
	free(table->philo[index].eat_count_lock);
	free(table->philo[index].full_eat_flag_lock);
	free(table->philo);
	free(table);
	return ;
}

void	only_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&philo->table->write_lock);
	printf("%ld %d has taken a fork\n", get_current_ms_time() \
			- philo->table->eat_start_time, philo->id);
	pthread_mutex_unlock(&philo->table->write_lock);
	ft_usleep(philo->table->dead_time);
	pthread_mutex_lock(&philo->table->write_lock);
	printf("%ld %d dead\n", get_current_ms_time() \
			- philo->table->eat_start_time, philo->id);
	pthread_mutex_unlock(&philo->table->write_lock);
	pthread_mutex_unlock(philo->left_fork);
	return ;
}
