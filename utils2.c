/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myerturk <myerturk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:59:57 by myerturk          #+#    #+#             */
/*   Updated: 2024/05/03 15:43:25 by myerturk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdio.h>

void	action_print(t_rules *rules, int id, char *string)
{
	pthread_mutex_lock(&(rules->dieded_check));
	if (!(rules->dieded))
	{
		printf("%lli ", timestamp() - rules->first_timestamp);
		printf("%i ", id + 1);
		printf("%s\n", string);
		usleep(50);
	}
	pthread_mutex_unlock(&(rules->dieded_check));
}

void	eat_control(t_rules *r, t_philosopher *p)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&(r->x_ate_check));
	while (r->nb_eat != -1 && i < r->nb_philo && p[i].x_ate >= r->nb_eat)
		i++;
	pthread_mutex_unlock(&(r->x_ate_check));
	if (i == r->nb_philo)
	{
		pthread_mutex_lock(&(r->all_ate_check));
		r->all_ate = 1;
		pthread_mutex_unlock(&(r->all_ate_check));
	}
}

void	philo_eats(t_philosopher *philo)
{
	t_rules	*rules;

	rules = philo->rules;
	pthread_mutex_lock(&(rules->forks[philo->left_fork_id]));
	pthread_mutex_lock(&(rules->forks[philo->right_fork_id]));
	action_print(rules, philo->id, "has taken a fork");
	action_print(rules, philo->id, "has taken a fork");
	action_print(rules, philo->id, "is eating");
	pthread_mutex_lock(&(rules->t_last_meal_check));
	philo->last_dinner_time = timestamp();
	pthread_mutex_unlock(&(rules->t_last_meal_check));
	smart_sleep(rules->eat_duration, rules);
	pthread_mutex_lock(&(rules->x_ate_check));
	(philo->x_ate)++;
	pthread_mutex_unlock(&(rules->x_ate_check));
	pthread_mutex_unlock(&(rules->forks[philo->left_fork_id]));
	pthread_mutex_unlock(&(rules->forks[philo->right_fork_id]));
}

void	smart_sleep(long long time, t_rules *rules)
{
	long long	i;

	i = timestamp();
	while (1)
	{
		if (time_diff(i, timestamp()) >= time)
			break ;
		pthread_mutex_lock(&(rules->dieded_check));
		if (rules->dieded)
		{
			pthread_mutex_unlock(&(rules->dieded_check));
			break ;
		}
		pthread_mutex_unlock(&(rules->dieded_check));
		usleep(50);
	}
}
