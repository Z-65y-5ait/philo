/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:22:08 by azaimi            #+#    #+#             */
/*   Updated: 2025/03/15 03:09:03 by azaimi           ###   ########.fr       */
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