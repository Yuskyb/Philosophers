#include "philo.h"

void	wait_start_dinner_time(t_table_info *table)
{
	while (table->eat_start_time > get_current_ms_time())
		continue ;
}

long	get_current_ms_time(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

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

void	free_fork(t_philo *philo)
{
	int	index;

	index = 0;
	while (philo->id != -1)
	{
		free(philo[index].left_fork);
		index++;
	}
	return ;
}
