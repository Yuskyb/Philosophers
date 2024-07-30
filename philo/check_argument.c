# include "philo.h"

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

bool	check_argument(int ac, char	**av, int *count)
{
	if (ac < 5 || ac > 6)
		return (false);
	if (check_argument_str(av) == false)
		return (false);
	if (ac == 6)
		*count = atoi(av[5]);
	else
		*count = 0;
	return (true);
}
