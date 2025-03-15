/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:25:54 by azaimi            #+#    #+#             */
/*   Updated: 2025/03/15 03:11:11 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <time.h>
# include <limits.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# define num_philos_max 200

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	bool			is_alive;
	int				eat_count;
	pthread_mutex_t	state_mutex;
	long long		last_eat_start_time;
}	t_philo;

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	int				fork_id;
	int				is_taken;
}	t_fork;

typedef struct s_args
{
	int		n_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	long long	start_time;
	int		simulation_running;
	int		n_time_philo_should_eat;
}	t_args;

typedef struct s_simulation
{
	t_args			args;
	t_philo			*philo;
	t_fork			*forks;
	pthread_mutex_t	sim_mutex;
	pthread_mutex_t	write_mutex;
	pthread_t		monitor_thread;
}	t_simulation;


long long	get_time();
long		ft_atoi(char *str);
int			is_numeric(char *str);
int			ft_parse(int argc, char **argv);
int			handle_args(int argc, char **argv);
t_args		*ft_init_args(int argc, char **argv);

#endif