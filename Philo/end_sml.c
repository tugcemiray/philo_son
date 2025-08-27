/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_sml.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tugcemirayalgan <tugcemirayalgan@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 18:15:56 by tukaraca          #+#    #+#             */
/*   Updated: 2025/08/27 03:43:42 by tugcemiraya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		pthread_join(data->philo[i].thread_id, NULL);
		i++;
	}
}

void	clean_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->stop_mutex);
	pthread_mutex_destroy(&data->eat_mutex);
	free(data->forks);
	free(data->philo);
}

void	end_sml(t_data *data)
{
	join_threads(data);
	clean_mutexes(data);
}

int	ft_is_space(int c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}
