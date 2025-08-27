/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tukaraca <tukaraca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 18:16:04 by tukaraca          #+#    #+#             */
/*   Updated: 2025/07/26 19:28:28 by tukaraca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	init_data(t_data *data, int argc, char **argv)
{
	data->philo_count = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->must_eat_count = ft_atoi(argv[5]);
	else
		data->must_eat_count = -1;
	if (data->philo_count <= 0 || data->time_to_die < 0
		|| data->time_to_eat < 0
		|| data->time_to_sleep < 0
		|| (argc == 6 && data->must_eat_count <= 0))
		return (1);
	data->end_sim = 0;
	data->all_ate_flag = 0;
	data->philo = NULL;
	data->forks = NULL;
	return (0);
}

int	init_mutex(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_count);
	if (!data->forks)
		return (1);
	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->stop_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->eat_mutex, NULL) != 0)
		return (1);
	return (0);
}

int	init_philos(t_data *data)
{
	int	i;

	data->philo = malloc(sizeof(t_philo) * data->philo_count);
	if (!data->philo)
	{
		free(data->forks);
		return (1);
	}
	i = 0;
	while (i < data->philo_count)
	{
		data->philo[i].id = i + 1;
		data->philo[i].eaten_meal = 0;
		data->philo[i].l_fork = &data->forks[i];
		data->philo[i].r_fork = &data->forks
		[(i + 1) % data->philo_count];
		data->philo[i].data = data;
		data->philo[i].last_meal_time = data->start_time;
		i++;
	}
	return (0);
}

int	init_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_create(&data->philo[i].thread_id,
				NULL, &routine, &data->philo[i]) != 0)
		{
			printf("Error: Thread creation failed for philosopher %d\n", i + 1);
			return (1);
		}
		usleep(100);
		i++;
	}
	return (0);
}
