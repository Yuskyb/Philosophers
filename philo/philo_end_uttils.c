#include	"philo.h"

bool	thread_end(t_table_info *table, t_philo *philo, int philo_count)
{
	pthread_t	*thread_index;
	int			index;

	index = 0;
	while (index < philo_count)
	{
		pthread_join(philo[index].thread, NULL);
		index++;
	}
	pthread_join(table->supervisor, NULL);
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
