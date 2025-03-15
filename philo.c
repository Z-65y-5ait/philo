/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:35:00 by azaimi            #+#    #+#             */
/*   Updated: 2025/03/15 18:23:16 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_simulation	*init_sim(int argc, char **argv)
{
	t_simulation *sim;

	sim = (t_simulation *)malloc(sizeof(t_simulation));
	if (!sim)
		return (NULL);
	if (!(sim->args = ft_init_args(argc, argv)))
		return (free(sim), NULL);
	if (!(sim->forks = ft_forks(&sim->args)))
		return (free(sim), NULL);
	if (!(sim->philo = ft_philoat(&sim->args, &sim->forks)))
		return (free(sim), NULL);
	if (pthread_mutex_init(&sim->sim_mutex, NULL) != 0
		|| pthread_mutex_init(&sim->write_mutex, NULL) != 0)
		return (free(sim), NULL);
	return (sim);
}

int main(int argc, char **argv)
{
	int i;
	pthread_t thread[4];

	i = 0;
	(void)argv;
	if (ft_parse(argc, argv) == 0)
		return (0);
	// pthread_mutex_init(&mutex, NULL);
	while (i < 4)
	{
		// if (pthread_create(thread + i, NULL, &comp, NULL) != 0)
			return (1);
		if (pthread_join(thread[i], NULL) != 0)
			return (2);
		i++;
	}
	// pthread_mutex_destroy(&mutex);
	// printf("m = %d", m);
	return (0);
}
