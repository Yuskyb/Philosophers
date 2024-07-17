#include	"philo.h"

void	thread_end(t_philo *philo, int philo_count)
{
	pthread_t	*thread_index;
	int			index;

	index = 0;
	thread_index = (pthread_t *)malloc(sizeof(pthread_t) * philo_count);
	if (thread_index == NULL)
		exit(0);
	while (index < philo_count)
	{
		philo[index].thread = thread_index[index];
		index++;
	}
	index = 0;
	while (index < philo_count)
	{
		pthred_join(&philo[i].thread, NULL);
		index++;
	}
	return ;
}

void	destroy_fork(t_philo *philo, int philo_count)
{
	int	index;

	index = 0;
	while (index < philo_count)
	{
		if (pthread_mutex_destroy(philo[index].fork) != 0)
			exit(0);
		index++;
	}
	return ;
}
