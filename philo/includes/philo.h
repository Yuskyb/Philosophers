/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:33:45 by yususato          #+#    #+#             */
/*   Updated: 2024/08/04 22:54:51 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <limits.h>
# include <string.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/time.h>

typedef struct s_table_info	t_table_info;

typedef struct s_philo
{
	t_table_info	*table;
	pthread_t		thread;
	int				id;
	int				eat_count;
	long			last_eat_time;
	bool			dead_flag;
	bool			full_eat_flag;
	pthread_mutex_t	*full_eat_flag_lock;
	pthread_mutex_t	*eat_count_lock;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philo;

typedef struct s_table_info
{
	t_philo			*philo;
	pthread_t		supervisor;
	int				philo_count;
	int				dead_time;
	long			eat_time;
	int				sleep_time;
	long			eat_start_time;
	int				eat_count_goal;
	bool			stop_flag;
	bool			eat_count_goal_flag;
	int				create_count;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	stop_lock;
}	t_table_info;
void	check_eat_flag(t_philo *philo);
void	fork_init(t_philo *philo, int philo_count);
void	leftfork_lock(t_philo *philo);
bool	lock_fork(t_philo *philo);
void	unlock_fork(t_philo *philo);
void	unlock_rightfork(t_philo *philo);
void	unlock_leftfork(t_philo *philo);
void	fork_lock(t_philo *philo);
bool	thread_end(t_table_info *table, t_philo *philo);
bool	destroy_fork(t_table_info *table, t_philo *philo, int philo_count);
bool	philo_thinking(t_philo *philo);
bool	philo_sleeping(t_philo *philo);
bool	ft_is_str(char	*str);
bool	thread_init(t_table_info *table_tmp, t_philo *philo_tmp \
					, int philo_count);
void	fork_mutex_init(pthread_mutex_t *fork, int philo_count);
void	fork_init(t_philo *philo, int philo_count);
void	free_fork(t_philo *philo);
void	free_thread(pthread_t *thread);
long	get_current_ms_time(void);
bool	check_argument(int ac, char	**av);
bool	table_philo_mutex_init(t_table_info *table \
		, t_philo *philo, int philo_count);
void	*supervisor_loop(void *argc);
bool	check_dead_philo(t_philo *philo);
void	wait_start_dinner_time(t_table_info *table);
void	only_philo(t_philo *philo);
void	ft_free_table(t_table_info *table);
void	ft_usleep(long time);
bool	check_philo_loop_dead(t_philo *philo);
void	handle_philo_dead(t_table_info *table, int index);
void	handle_full_eat_count(t_table_info *table, int index);
bool	ft_is_str(char	*str);
void	*philo_loop(void *arg);
int		ft_atoi(const char *str);
int		ft_atoi_check(const char *str, bool *flag);
bool	check_stop_flag(t_table_info *table);
void	check_full_eat_flag(t_philo *philo);
bool	observe_full_eat_flag(t_philo *philo);
bool	check_stop_flag_write(t_table_info *table);
void	check_main_stop_flag(t_table_info *table);

#endif