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

void	leftfork_lock(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	printf("Philosopher %d  has taken a fork\n", philo->id);
}

void	rightfork_lock(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	printf("Philosopher %d  has taken a fork\n", philo->id);
}

void	fork_lock(t_philo *philo, int philo_count)
{
	leftfork_lock(philo);
	rightfork_lock(philo);
}