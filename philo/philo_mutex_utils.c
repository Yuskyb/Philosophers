/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_mutex_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 16:13:25 by yususato          #+#    #+#             */
/*   Updated: 2024/08/04 16:14:07 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_eat_flag(t_philo *philo)
{
	pthread_mutex_lock(philo->eat_count_lock);
	if (philo->table->eat_count_goal == philo->eat_count)
	{
		pthread_mutex_unlock(philo->eat_count_lock);
		check_full_eat_flag(philo);
		return ;
	}
	pthread_mutex_unlock(philo->eat_count_lock);
	return ;
}

void	check_full_eat_flag(t_philo *philo)
{
	pthread_mutex_lock(philo->full_eat_flag_lock);
	philo->full_eat_flag = true;
	pthread_mutex_unlock(philo->full_eat_flag_lock);
	return ;
}

bool	observe_full_eat_flag(t_philo *philo)
{
	pthread_mutex_lock(philo->full_eat_flag_lock);
	if (philo->full_eat_flag == true)
	{
		pthread_mutex_unlock(philo->full_eat_flag_lock);
		return (true);
	}
	pthread_mutex_unlock(philo->full_eat_flag_lock);
	return (false);
}
