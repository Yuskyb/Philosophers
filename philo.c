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

#include	"philo.h"

int	main(int ac, char **av)
{
	t_philo			*philo;
	pthread_mutex_t	*forks;
	int				count;

	(void)ac;
	if (ac < 5 || ac > 6)
		return (0);
	if (ac == 6)
		count = atoi(av[5]);
	else
		count = 0;
	philo = philo_init(atoi(av[1]), atoi(av[2]), atoi(av[3]) \
				,atoi(av[4]), count);
	if (philo == NULL)
		return (0);
	fork_init(philo, atoi(av[1]));
	thread_init(philo, atoi(av[1]));
	thread_end(philo, atoi(av[1]));
	destroy_fork(philo, atoi(av[1]));
	return (0);
}
