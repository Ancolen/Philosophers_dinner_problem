/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcopoglu <bcopoglu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 14:52:09 by bcopoglu          #+#    #+#             */
/*   Updated: 2023/12/10 15:02:32 by bcopoglu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>
#include "philo.h"
#include <stdlib.h>

long long	timestamp(void)
{
	struct timeval	t;
	long long		time;

	gettimeofday(&t, NULL);
	time = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	return (time);
}

long long	time_diff(long long past, long long now)
{
	return (now - past);
}

int	write_error(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	write(2, "Error: ", 7);
	write(2, str, len);
	write(2, "\n", 1);
	return (1);
}

void	ft_free(t_rules *rules)
{
	free (rules->forks);
	free (rules->philosophers);
}
