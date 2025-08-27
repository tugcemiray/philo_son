/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tugcemirayalgan <tugcemirayalgan@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 03:13:45 by tugcemiraya       #+#    #+#             */
/*   Updated: 2025/08/27 03:40:38 by tugcemiraya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

# define INT_MAX	2147483647
# define INT_MIN	-2147483648

typedef struct s_data
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	int				end_sim;
	int				all_ate_flag;

	long			start_time;

	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	eat_mutex;

	struct s_philo	*philo;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				eaten_meal;
	long			last_meal_time;

	pthread_t		thread_id;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;

	t_data			*data;
}	t_philo;

int			check_args(int argc, char **argv);
int			init_data(t_data *data, int argc, char **argv);
int			init_mutex(t_data *data);
int			init_philos(t_data *data);
int			init_threads(t_data *data);
int			start_sml(t_data *data);
void		*routine(void *arg);
void		*monitor_thread(void *arg);
void		print_action(t_philo *philo, char *msg);
void		take_forks(t_philo *philo);
void		eat(t_philo *philo);
void		drop_forks(t_philo *philo);
long long	get_time(void);
void		my_sleep(long duration, t_data *data);
int			get_sim_end(t_data *data);
void		set_sim_end(t_data *data, int value);
void		end_sml(t_data *data);
void		join_threads(t_data *data);
void		clean_mutexes(t_data *data);
int			ft_atoi(char *str);
int			is_digit(char *str);
int			ft_strcmp(const char *s1, const char *s2);
int			check_all_ate(t_data *data);
int			ft_is_space(int c);

#endif
