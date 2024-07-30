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

void	unlock_leftfork(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
}

void	unlock_rightfork(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
}

void	unlock_fork(t_philo *philo)
{

		unlock_leftfork(philo);
		unlock_rightfork(philo);

}