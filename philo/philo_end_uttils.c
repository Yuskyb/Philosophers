/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_end_uttils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 11:54:49 by yususato          #+#    #+#             */
/*   Updated: 2024/08/04 17:18:18 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philo.h"

bool	thread_end(t_table_info *table, t_philo *philo)
{
	int	index;
	int	tmp;

	index = 0;
	tmp = 0;
	if (table->create_count != -1)
		tmp = table->create_count;
	while (index < tmp)
	{
		if (pthread_join(philo[index].thread, NULL) != 0)
			return (false);
		index++;
	}
	if (table->create_count == -1 \
		|| pthread_join(table->supervisor, NULL) != 0)
		return (false);
	return (true);
}

bool	destroy_fork(t_table_info *table, t_philo *philo, int philo_count)
{
	int	index;

	index = 0;
	if (pthread_mutex_destroy(&table->stop_lock) != 0)
		return (false);
	if (pthread_mutex_destroy(&table->write_lock) != 0)
		return (false);
	while (index < philo_count)
	{
		if (pthread_mutex_destroy(philo[index].left_fork) != 0)
			return (false);
		if (pthread_mutex_destroy(philo[index].eat_count_lock) != 0)
			return (false);
		index++;
	}
	return (true);
}
