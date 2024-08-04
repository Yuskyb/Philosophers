/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:40:14 by yususato          #+#    #+#             */
/*   Updated: 2024/08/04 22:56:34 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(long time)
{
	long	start;

	start = get_current_ms_time();
	while (get_current_ms_time() - start < time)
		usleep(1 / 100000);
	return ;
}

bool	philo_thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->write_lock);
	if (check_stop_flag_write(philo->table) == true)
		return (false);
	printf("%ld %d is thinking\n", get_current_ms_time() \
			- philo->table->eat_start_time, philo->id);
	pthread_mutex_unlock(&philo->table->stop_lock);
	pthread_mutex_unlock(&philo->table->write_lock);
	return (true);
}

bool	philo_sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->write_lock);
	if (check_stop_flag_write(philo->table) == true)
		return (false);
	printf("%ld %d is sleeping\n", get_current_ms_time() \
			- philo->table->eat_start_time, philo->id);
	pthread_mutex_unlock(&philo->table->stop_lock);
	pthread_mutex_unlock(&philo->table->write_lock);
	ft_usleep(philo->table->sleep_time);
	return (true);
}

bool	philo_eating(t_philo *philo)
{
	if (lock_fork(philo) == false)
		return (false);
	pthread_mutex_lock(&philo->table->write_lock);
	if (check_philo_loop_dead(philo) == false)
		return (false);
	printf("%ld %d is eating\n", get_current_ms_time() \
			- philo->table->eat_start_time, philo->id);
	pthread_mutex_unlock(&philo->table->stop_lock);
	pthread_mutex_unlock(&philo->table->write_lock);
	pthread_mutex_lock(philo->eat_count_lock);
	philo->eat_count++;
	pthread_mutex_unlock(philo->eat_count_lock);
	philo->last_eat_time = get_current_ms_time();
	ft_usleep(philo->table->eat_time);
	unlock_fork(philo);
	return (true);
}

void	*philo_loop(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_start_dinner_time(philo->table);
	if (philo->table->philo_count == 1)
		return (only_philo(philo), NULL);
	if (philo->id % 2 != 0)
		ft_usleep(philo->table->eat_time);
	while (true)
	{
		if (philo_eating(philo) == false)
			return (NULL);
		check_eat_flag(philo);
		if (philo_sleeping(philo) == false)
			return (NULL);
		if (philo_thinking(philo) == false)
			return (NULL);
		if (philo->table->eat_count_goal == philo->eat_count)
			return (NULL);
	}
	return (NULL);
}
