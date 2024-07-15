#include "philo.h"

void	leftfork_lock(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	printf("Philosopher %d  has taken a fork\n", philo->id);
}

void	rightfork_lock(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	printf("Philosopher %d  has taken a fork\n", philo->id);
}

void	fork_destroy(t_philo *philo, int philo_count)
{
	leftfork_unlock(philo);
	rightfork_unlock(philo);
}