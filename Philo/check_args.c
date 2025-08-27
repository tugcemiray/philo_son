/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tugcemirayalgan <tugcemirayalgan@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 18:15:47 by tukaraca          #+#    #+#             */
/*   Updated: 2025/08/27 03:44:25 by tugcemiraya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_atoi(char *str)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+')
		i++;
	if (str[i] < '0' || str[i] > '9')
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i++] - '0');
		if (result > INT_MAX)
			return (-1);
	}
	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] != '\0')
		return (-1);
	return (result);
}

int	is_char_digit(char c)
{
	return (c >= '0' && c <= '9');
}

int	is_digit(char *str)
{
	int	i;
	int	has_digit;

	i = 0;
	has_digit = 0;
	if (!str || !*str)
		return (0);
	while (str[i] && ft_is_space(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	while (is_char_digit(str[i]))
	{
		has_digit = 1;
		i++;
	}
	while (str[i] && ft_is_space(str[i]))
		i++;
	return (has_digit && str[i] == '\0');
}

int	is_arg_digit(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!is_digit(argv[i]))
			return (1);
		i++;
	}
	return (0);
}

int	check_args(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	if (argc != 5 && argc != 6)
		return (1);
	if (is_arg_digit(argc, argv))
		return (1);
	while (++i < argc)
	{
		j = ft_atoi(argv[i]);
		if (j <= 0)
			return (1);
	}
	return (0);
}
