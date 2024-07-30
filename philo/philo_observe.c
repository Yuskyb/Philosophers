# include "philo.h"

bool	check_full_eat_count(t_philo *philo, int index)
{
	if (philo[index].eat_count == philo[index].eat_count_goal)
		return (true);
	return (false);
}

void	dead_philo(t_philo *philo)
{
	philo->dead_flag = true;
	return ;
}

bool	check_dead_philo(t_philo *philo)
{
	if (philo->dead_flag == true)
		return (true);
	if (!philo->last_eat_time)
		philo->last_eat_time = philo->table->eat_start_time;
	if (get_current_ms_time() - philo->last_eat_time \
		 > philo->table->dead_time)
	{
		philo->dead_flag = true;
		return (true);
	}
	return (false);
}

bool	check_dead(t_philo *philo, int index)
{
	if (philo[index].dead_flag == true)
		return (true);
	if (check_dead_philo(&philo[index]))
		return (true);
	return (false);
}

void	*supervisor_loop(void *argc)
{
	int				index;
	t_table_info	*table;

	table = (t_table_info *)argc;
	wait_start_dinner_time(table);
	if (table->philo_count == 1)
		return (NULL);
	while (table->stop_flag == false)
	{
		index = 0;
		while (index < table->philo_count)
		{
			pthread_mutex_lock(table->philo[index].eat_count_lock);
			if (check_dead(table->philo, index))
			{
				pthread_mutex_lock(&table->stop_lock);
				table->stop_flag = true;
				pthread_mutex_lock(&table->write_lock);
				// printf("philo%ld\n",get_current_ms_time() - table->philo[index].last_eat_time);
				printf("%ld %d dead\n", get_current_ms_time() - table->eat_start_time, table->philo[index].id);
				pthread_mutex_unlock(&table->write_lock);
				pthread_mutex_unlock(&table->stop_lock);
				pthread_mutex_unlock(table->philo[index].eat_count_lock);
				return (NULL);
			}
			if (table->eat_count_goal_flag == true && check_full_eat_count(table->philo, index))
			{
				pthread_mutex_lock(&table->stop_lock);
				table->stop_flag = true;
				pthread_mutex_unlock(&table->stop_lock);
				pthread_mutex_unlock(table->philo[index].eat_count_lock);
				return (NULL);
			}
			pthread_mutex_unlock(table->philo[index].eat_count_lock);
			index++;
		}
	}
	return (NULL);
}

void	only_philo(t_philo *philo)
{
	if (philo->table->philo_count == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		printf("%ld %d has taken a fork\n", get_current_ms_time() - philo->table->eat_start_time, philo->id);
		printf("%ld %d dead\n", get_current_ms_time() - philo->table->eat_start_time, philo->id);
		pthread_mutex_unlock(philo->left_fork);
	}
	return ;
}
