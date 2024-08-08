/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:33:11 by yususato          #+#    #+#             */
/*   Updated: 2024/08/04 17:20:56 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_table_info	*table_init(int count_tmp \
			, int dead_tmp, int eat_tmp, int sleep_tmp)
{
	t_table_info	*table;

	table = (t_table_info *)malloc(sizeof(t_table_info));
	if (table == NULL)
		return (NULL);
	table->philo_count = count_tmp;
	table->dead_time = dead_tmp;
	table->eat_time = eat_tmp;
	table->sleep_time = sleep_tmp;
	table->stop_flag = false;
	return (table);
}

t_philo	*philo_init(int count_tmp)
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
		philo[index].full_eat_flag = false;
		index++;
	}
	philo[index].id = -1;
	return (philo);
}

bool	set_eat_count(t_philo *philo, int len \
					, char *eat_str, t_table_info *table)
{
	int			index;

	index = 0;
	if (len == 6)
	{
		table->eat_count_goal = ft_atoi(eat_str);
		table->eat_count_goal_flag = true;
	}
	else
		table->eat_count_goal_flag = false;
	while (index < table->philo_count)
	{
		philo[index].table = table;
		index++;
	}
	return (true);
}

void	print_error_message(void)
{
	printf("Error argument\n");
	return ;
}

int	main(int ac, char **av)
{
	t_philo			*philo;
	t_table_info	*table;

	if (check_argument(ac, av) == false)
		return (print_error_message(), 0);
	philo = philo_init(ft_atoi(av[1]));
	if (philo == NULL)
		return (0);
	table = table_init(ft_atoi(av[1]), ft_atoi(av[2]), ft_atoi(av[3]) \
						, ft_atoi(av[4]));
	if (table == NULL)
		return (free(philo), 0);
	if (set_eat_count(philo, ac, av[5], table) == false)
		return (free(philo), 0);
	if (table_philo_mutex_init(table, philo, ft_atoi(av[1])) == false)
		return (0);
	if (thread_init(table, philo, ft_atoi(av[1])) == false)
		check_main_stop_flag(table);
	if (thread_end(table, philo) == false)
		return (ft_free_table(table), 0);
	if (destroy_fork(table, philo, ft_atoi(av[1])) == false)
		return (ft_free_table(table), 0);
	ft_free_table(table);
	return (0);
}

// __attribute__((destructor)) static void destructor()
// {
//     system("leaks -q philo");
// }