/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_lock.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:40:21 by yususato          #+#    #+#             */
/*   Updated: 2024/07/16 13:40:22 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_leftfork(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&philo->table->write_lock);
	if (philo->table->stop_flag == true)
	{
		pthread_mutex_unlock(&philo->table->write_lock);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	printf("%ld %d has taken left a fork\n", get_current_ms_time() - philo->table->eat_start_time, philo->id);
	pthread_mutex_unlock(&philo->table->write_lock);
}

void	lock_rightfork(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&philo->table->write_lock);
	if (philo->table->stop_flag == true)
	{
		pthread_mutex_unlock(&philo->table->write_lock);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	printf("%ld %d has taken right a fork\n", get_current_ms_time() - philo->table->eat_start_time, philo->id);
	pthread_mutex_unlock(&philo->table->write_lock);
}

void	lock_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		lock_leftfork(philo);
		lock_rightfork(philo);
	}
	else
	{
		lock_rightfork(philo);
		lock_leftfork(philo);
	}
}