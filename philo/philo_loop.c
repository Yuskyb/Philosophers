/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:40:14 by yususato          #+#    #+#             */
/*   Updated: 2024/07/16 13:40:15 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(long time)
{
	long	start;

	start = get_current_ms_time();
	while (get_current_ms_time() - start < time)
		usleep((time * 1000) / 100000);
	return ;
}

void	philo_thinking(t_philo *philo)
{

	pthread_mutex_lock(&philo->table->write_lock);
	if (philo->table->stop_flag == true)
	{
		pthread_mutex_unlock(&philo->table->write_lock);
		return ;
	}
	printf("%ld %d is thinking\n", get_current_ms_time() - philo->table->eat_start_time, philo->id);
	pthread_mutex_unlock(&philo->table->write_lock);
}

void	philo_sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->write_lock);
	if (philo->table->stop_flag == true)
	{
		pthread_mutex_unlock(&philo->table->write_lock);
		return ;
	}
	printf("%ld %d is sleeping\n", get_current_ms_time() - philo->table->eat_start_time, philo->id);
	pthread_mutex_unlock(&philo->table->write_lock);
		ft_usleep(philo->table->sleep_time);
}

void	philo_eating(t_philo *philo)
{
	lock_fork(philo);
	if (check_dead_philo(philo) == true)
	{
		pthread_mutex_lock(&philo->table->stop_lock);
		philo->table->stop_flag = true;
		pthread_mutex_unlock(&philo->table->stop_lock);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	pthread_mutex_lock(&philo->table->write_lock);
	if (philo->table->stop_flag == true)
	{
		pthread_mutex_unlock(&philo->table->write_lock);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	printf("%ld %d is eating\n", get_current_ms_time() - philo->table->eat_start_time, philo->id);
	pthread_mutex_unlock(&philo->table->write_lock);
	pthread_mutex_lock(philo->eat_count_lock);
	philo->eat_count++;
	philo->last_eat_time = get_current_ms_time();
	pthread_mutex_unlock(philo->eat_count_lock);
		ft_usleep(philo->table->eat_time);
	unlock_fork(philo);
}

void	*philo_loop(void *arg)
{
	t_philo *philo;


	philo = (t_philo *)arg;
	wait_start_dinner_time(philo->table);
	if (philo->table->philo_count == 1)
		return (only_philo(philo), NULL);
	if (philo->id % 2 != 0)
		ft_usleep(philo->table->eat_time);
	while (philo->table->stop_flag == false)
	{
		philo_eating(philo);
		if (philo->table->stop_flag == true)
			break;
		philo_sleeping(philo);
		if (philo->table->stop_flag == true)
			break;
		philo_thinking(philo);
	}
	return (NULL);
}