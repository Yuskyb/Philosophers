#include "philo.h"

void	free_thread(pthread_t *thread)
{
	int	index;

	index = 0;
	while (thread[index])
	{
		free(thread[index]);
		index++;
	}
	return ;
}

void	free_fork(t_mutex_thread *fork)
{
	int	index;

	index = 0;
	while (fork[index])
	{
		free(fork[index]);
		index++;
	}
	return ;
}