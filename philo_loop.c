#include "philo.h"

void	philo_thinking(t_philo *philo)
{
	printf("Philosopher %d is thinking", philo->id);
	usleep(rand() )
}

void	philo_sleeping(t_philo *philo)
{
	printf("Philosopher %d is sleeping", philo->id);
	usleep(rand() )
}

void	philo_eating(t_philo *philo)
{
	printf("Philosopher %d is eating", philo->id);
	usleep(rand() )
}

void	philo_loop(t_philo *philo, int philo_count)
{
	while (true)
	{
		fork_lock(philo);
		philo_eating(philo);
		philo_sleeping(philo);
		philo_thinking(philo);
	}
}