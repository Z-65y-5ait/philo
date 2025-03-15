/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:22:08 by azaimi            #+#    #+#             */
/*   Updated: 2025/03/15 17:48:43 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi(char *str)
{
	int			i;
	int			sign;
	long		result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		if ((result * sign) > INT_MAX || (result * sign) < INT_MIN)
			return (INT_MAX + (long)1);
		i++;
	}
	return (result * sign);
}

int	is_numeric(char *str)
{
	int i;

	if (!str || *str == '\0')
		return (0);
	i = 0;
	if (str[0] == '+')
		i++;
	while (str[i])
	{
		if(str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	handle_args(int argc, char **argv)
{
	int i;

	i = 1;
	while (i < argc)
	{
		if (is_numeric(argv[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

t_args	*ft_init_args(int argc, char **argv)
{
	t_args	*arg;

	arg = (t_args *)malloc(sizeof(t_args));
	if (!arg)
		return (NULL);
	arg->n_philo = ft_atoi(argv[1]);
	arg->time_to_die = ft_atoi(argv[2]);
	arg->time_to_eat = ft_atoi(argv[3]);
	arg->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		arg->n_time_philo_should_eat = ft_atoi(argv[5]);
	else
		arg->n_time_philo_should_eat = -1;
	if (arg->n_philo <= 0 || arg->time_to_die <= 0
		|| arg->time_to_eat <= 0 || arg->time_to_sleep <= 0
		|| (argc == 6 && arg->n_time_philo_should_eat <= 0))
	{
		free(arg);
		return (NULL);
	}
	arg->simulation_running = true;
	arg->start_time = get_time();
	return (arg);
}

long long	get_time()
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000 + tv.tv_usec / 1000));
}

int	ft_parse(int argc, char **argv)
{
	if (handle_args(argc, argv) == 0 || (argc != 5 && argc != 6))
	{
		printf("<./philo> ");
		printf("<number_of_philosophers> ");
		printf("<time_to_die> ");
		printf("<time_to_eat> ");
		printf("<time_to_sleep> ");
		printf("<optional_number_of_times_each_philosopher_must_eat>\n");
		return (0);
	}
	return (1);
}

void	ft_destroy(pthread_mutex_t *mutex, int count)
{
	int	i;

	i = 0;
	while(i < count)
		pthread_mutex_destroy(&mutex[i++]);
}

pthread_mutex_t	*ft_forks(t_args *arg)
{
	int				i;
	t_fork	*forks;

	i = 0;
	forks = (t_fork *)malloc(sizeof(t_fork) * arg->n_philo);
	if(!forks)
		return (NULL);
	while (i < arg->n_philo)
	{
		forks[i].fork_id = i;
		forks[i].is_taken = 0;
		if (pthread_mutex_init(&forks[i].mutex, NULL) != 0)
		{
			ft_destroy(forks, i);
			free(forks);
			return (NULL);
		}
		i++;
	}
	return (forks);
}

pthread_mutex_t	*ft_state_mutex(t_args *arg)
{
	int				i;
	pthread_mutex_t	*state;

	i = 0;
	state = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * arg->n_philo);
	if(!state)
		return (NULL);
	while (i < arg->n_philo)
	{
		if (pthread_mutex_init(&state[i], NULL) != 0)
		{
			ft_destroy(state, i);
			free(state);
			return (NULL);
		}
		i++;
	}
	return (state);
}

void	ft_destroy_forks(t_fork *fork)
{
	int	i;

	i = 0;
	while(--i)
		pthread_mutex_destroy(&fork[i].mutex);
}

t_philo	*ft_philoat(t_args *arg, t_fork *forks)
{
	int				i;
	pthread_mutex_t	*state;
	t_philo			*philoat;

	i = 0;
	state = ft_state_mutex(arg);
	if (!state)
		return (ft_destroy(forks, arg->n_philo), free(forks), NULL);
	philoat = (t_philo *)malloc(sizeof(t_philo) * arg->n_philo);
	if(!philoat)
		return (ft_destroy(state, arg->n_philo), free(state), ft_destroy_forks(forks), free(forks), NULL);
	while(i < arg->n_philo)
	{
		philoat[i].id = i;
		philoat[i].is_alive = true;
		philoat[i].last_eat_start_time = get_time();
		philoat[i].eat_count = 0;
		philoat[i].state_mutex = &state[i];
		philoat[i].l_fork = &forks[i];
		philoat[i].r_fork = &forks[(i + 1) % arg->n_philo];
		philoat[i].args = arg;
		i++;
	}
	return (philoat);
}

