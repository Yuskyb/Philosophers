/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:33:11 by yususato          #+#    #+#             */
/*   Updated: 2024/07/12 22:05:53 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_table_info	*table_init(t_philo *philo, int count_tmp \
			, int dead_tmp, int eat_tmp, int sleep_tmp)
{
	t_table_info	*table;

	table = (t_table_info *)malloc(sizeof(t_table_info));
	table->philo_count = count_tmp;
	table->dead_time = dead_tmp;
	table->eat_time = eat_tmp;
	table->sleep_time = sleep_tmp;
	table->stop_flag = false;
	return (table);
}

t_philo	*philo_init(int count_tmp, int goal_tmp)
{
	t_philo	*philo;
	int		index;

	index = 0;
	philo = (t_philo *)malloc(sizeof(t_philo) * (count_tmp + 1));
	if (philo == NULL)
		return (NULL);
	while (index < count_tmp)
	{
		philo[index].id = index + 1;
		philo[index].eat_count = 0;
		philo[index].dead_flag = false;
		index++;
	}
	philo[index].id = -1;
	return (philo);
}

int	main(int ac, char **av)
{
	t_philo			*philo;
	t_table_info	*table;
	pthread_mutex_t	*forks;
	int				count;

	if (check_argument(ac,av, &count) == false)
		return (0);
	philo = philo_init(atoi(av[1]), count);
	if (philo == NULL)
		return (0);
	table = table_init(philo, atoi(av[1]), atoi(av[2]), atoi(av[3]) \
				,atoi(av[4]));
	if (table == NULL)
		return (0);
	if (table_philo_mutex_init(table, philo, atoi(av[1])) == false)
		return (0);
	if (ac == 6)
	{
		table->eat_count_goal = atoi(av[5]);
		table->eat_count_goal_flag = true;
	}
	else
		table->eat_count_goal_flag = false;
	if (thread_init(table, philo, atoi(av[1])) == false)
		return (0);
	if (thread_end(table,philo, atoi(av[1])) == false)
		return (0);
	if (destroy_fork(table, philo, atoi(av[1])) == false)
		return (0);
	return (0);
}
