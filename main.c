/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myerturk <myerturk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:59:10 by myerturk          #+#    #+#             */
/*   Updated: 2024/05/03 15:54:06 by myerturk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

int	parse_to_values(t_rules *rules, char **argv)
{
	rules->nb_philo = ft_atoi(argv[1]);
	rules->death_drtion = ft_atoi(argv[2]);
	rules->eat_duration = ft_atoi(argv[3]);
	rules->sleep_duration = ft_atoi(argv[4]);
	rules->all_ate = 0;
	rules->dieded = 0;
	if (rules->nb_philo <= 0 || rules->death_drtion <= 0
		|| rules->eat_duration <= 0 || rules->sleep_duration <= 0)
		return (1);
	if (argv[5])
	{
		rules->nb_eat = ft_atoi(argv[5]);
		if (rules->nb_eat <= 0)
			return (1);
	}
	else
		rules->nb_eat = -1;
	return (0);
}

int	philo_init(t_rules *rules)
{
	int	i;

	i = rules->nb_philo;
	rules->philosophers = malloc(sizeof(t_philosopher) * i);
	if (!(rules->philosophers))
		return (1);
	while (--i >= 0)
	{
		rules->philosophers[i].id = i;
		rules->philosophers[i].x_ate = 0;
		rules->philosophers[i].left_fork_id = i;
		rules->philosophers[i].right_fork_id = (i + 1) % rules->nb_philo;
		rules->philosophers[i].last_dinner_time = 0;
		rules->philosophers[i].rules = rules;
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int			i;
	int			result;
	int			sign;

	i = 0;
	result = 0;
	sign = 1;
	while (str[i] <= 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (sign * result);
}

int	ft_isdigit(char **array)
{
	int	i;
	int	j;

	i = 1;
	while (array[i])
	{
		j = 0;
		while (array[i][j])
		{
			if (!(array[i][j] >= '0' && array[i][j] <= '9'))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_rules	rules;

	if (argc < 5)
		return (write_error("There are not enough arguments!"), 0);
	if (ft_isdigit(argv))
		return (write_error("Invalid Character!"), 0);
	if (parse_to_values(&rules, argv))
		return (write_error("Parse error!"), 0);
	if (philo_init(&rules))
		return (write_error("Philo Init Error"), 0);
	if (init_mutex(&rules))
		return (write_error("Mutex Init Error"), 0);
	if (philo_main(&rules))
		return (write_error("Thread Create Error"), 0);
}
