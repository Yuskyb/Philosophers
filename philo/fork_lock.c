/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_lock.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:40:21 by yususato          #+#    #+#             */
/*   Updated: 2024/08/04 22:58:01 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	lock_leftfork(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&philo->table->write_lock);
	if (check_stop_flag_write(philo->table) == true)
	{
		pthread_mutex_unlock(philo->left_fork);
		return (false);
	}
	printf("%ld %d has taken a fork\n", get_current_ms_time() \
			- philo->table->eat_start_time, philo->id);
	pthread_mutex_unlock(&philo->table->stop_lock);
	pthread_mutex_unlock(&philo->table->write_lock);
	return (true);
}

bool	lock_rightfork(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&philo->table->write_lock);
	if (check_stop_flag_write(philo->table) == true)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (false);
	}
	printf("%ld %d has taken a fork\n", \
		get_current_ms_time() - philo->table->eat_start_time, philo->id);
	pthread_mutex_unlock(&philo->table->stop_lock);
	pthread_mutex_unlock(&philo->table->write_lock);
	return (true);
}

bool	lock_fork(t_philo *philo)
{
	if (lock_leftfork(philo) == false)
		return (false);
	if (lock_rightfork(philo) == false)
		return (false);
	return (true);
}
