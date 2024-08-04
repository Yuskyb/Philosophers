/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argument.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 11:54:42 by yususato          #+#    #+#             */
/*   Updated: 2024/08/01 11:49:12 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_is_str(char	*str)
{
	int	index;

	index = 0;
	while (str[index])
	{
		if ('0' <= str[index] && str[index] <= '9')
			index++;
		else
			return (false);
	}
	return (true);
}

bool	check_argument_str(char	**av)
{
	int	index;

	index = 1;
	while (av[index])
	{
		if (ft_is_str(av[index]) == false)
			return (false);
		index++;
	}
	return (true);
}

bool	check_argument(int ac, char	**av)
{
	int		index;
	bool	flag;

	index = 0;
	if (ac < 5 || ac > 6 || check_argument_str(av) == false)
		return (false);
	while (av[index])
	{
		flag = false;
		ft_atoi_check(av[index], &flag);
		if (flag == true)
			return (false);
		if (index == 1 && ft_atoi(av[1]) > 200)
			return (false);
		flag = false;
		index++;
	}
	return (true);
}
