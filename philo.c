/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:35:00 by azaimi            #+#    #+#             */
/*   Updated: 2025/03/15 02:32:43 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t mutex;
int m = 0;

void *comp()
{
	long long i = 0;
	while (i < 1000000)
	{
		pthread_mutex_lock(&mutex);
		m++;
		pthread_mutex_unlock(&mutex);
		i++;
	}
	return (NULL);
}

int main(int argc, char **argv)
{
	int i;
	pthread_t thread[4];

	i = 0;
	(void)argv;
	if (ft_parse(argc, argv) == 0)
		return (0);
	pthread_mutex_init(&mutex, NULL);
	while (i < 4)
	{
		if (pthread_create(thread + i, NULL, &comp, NULL) != 0)
			return (1);
		if (pthread_join(thread[i], NULL) != 0)
			return (2);
		i++;
	}
	pthread_mutex_destroy(&mutex);
	printf("m = %d", m);
	return (0);
}
