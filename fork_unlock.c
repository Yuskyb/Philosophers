/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_unlock.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:40:19 by yususato          #+#    #+#             */
/*   Updated: 2024/07/16 13:40:20 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	leftfork_lock(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	printf("Philosopher %d  has taken a fork\n", philo->id);
}

void	rightfork_lock(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	printf("Philosopher %d  has taken a fork\n", philo->id);
}

void	fork_destroy(t_philo *philo, int philo_count)
{
	leftfork_unlock(philo);
	rightfork_unlock(philo);
}