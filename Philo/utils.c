/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tukaraca <tukaraca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 18:16:36 by tukaraca          #+#    #+#             */
/*   Updated: 2025/07/26 19:29:47 by tukaraca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	print_action(t_philo *philo, char *msg)
{
	long	time;

	time = get_time() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->print_mutex);
	if (get_sim_end(philo->data) && ft_strcmp(msg, "died") != 0)
	{
		pthread_mutex_unlock(&philo->data->print_mutex);
		return ;
	}
	printf("%ld %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	my_sleep(long duration, t_data *data)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < duration)
	{
		if (get_sim_end(data))
			break ;
		usleep(100);
	}
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}
