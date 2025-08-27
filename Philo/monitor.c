/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tugcemirayalgan <tugcemirayalgan@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 18:16:21 by tukaraca          #+#    #+#             */
/*   Updated: 2025/08/27 00:11:35 by tugcemiraya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	is_philo_death(t_data *data)
{
	int		i;
	long	time_since_last_meal;

	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_lock(&data->eat_mutex);
		time_since_last_meal = get_time() - data->philo[i].last_meal_time;
		pthread_mutex_unlock(&data->eat_mutex);
		if (time_since_last_meal > data->time_to_die)
		{
			print_action(&data->philo[i], "died");
			set_sim_end(data, 1);
			return (1);
		}
		i++;
	}
	return (0);
}

int	get_sim_end(t_data *data)
{
	int	result;

	pthread_mutex_lock(&data->stop_mutex);
	result = data->end_sim;
	pthread_mutex_unlock(&data->stop_mutex);
	return (result);
}

void	set_sim_end(t_data *data, int value)
{
	pthread_mutex_lock(&data->stop_mutex);
	data->end_sim = value;
	pthread_mutex_unlock(&data->stop_mutex);
}

int	check_all_ate(t_data *data)
{
	int	i;

	if (data->must_eat_count <= 0)
		return (0);
	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_lock(&data->eat_mutex);
		if (data->philo[i].eaten_meal < data->must_eat_count)
		{
			pthread_mutex_unlock(&data->eat_mutex);
			return (0);
		}
		pthread_mutex_unlock(&data->eat_mutex);
		i++;
	}
	set_sim_end(data, 1);
	return (1);
}

void	*monitor_thread(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	usleep(500);
	while (!get_sim_end(data))
	{
		if (is_philo_death(data))
			return (NULL);
		if (check_all_ate(data))
			return (NULL);
		usleep(100);
	}
	return (NULL);
}
