/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-idri <ael-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 17:49:42 by ael-idri          #+#    #+#             */
/*   Updated: 2022/07/23 18:19:44 by ael-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	philos_full(t_philo **philo)
{
	if ((*philo)->required_meals == 0 && (*philo)->philo_full == 0)
	{
		(*philo)->info->philos_full++;
		(*philo)->philo_full = 1;
		if ((*philo)->info->philos_full == (*philo)->info->philo_nb)
		{
			pthread_mutex_lock(&((*philo)->info->message));
			printf("%lld: philosophers are full\n",
				time_after_create((*philo)->time_create));
			return (1);
		}
	}
	return (0);
}

int	philo_died(t_philo *philo)
{
	if (philo->last_meal == -1
		&& (time_after_create(philo->time_create) > philo->info->die_time))
	{
		pthread_mutex_lock(&(philo->info->message));
		printf("%lld: %d died\n",
			time_after_create(philo->time_create), philo->id);
		return (1);
	}
	else if (philo->last_meal != -1
		&& (current_time() - philo->last_meal) > philo->info->die_time)
	{
		pthread_mutex_lock(&(philo->info->message));
		printf("%lld: %d died\n",
			time_after_create(philo->time_create), philo->id);
		return (1);
	}
	return (0);
}

int	monitoring(t_philo **philo)
{
	while (*philo)
	{
		if (philos_full(philo))
			return (stop_routines(philo));
		if (philo_died(*philo))
			return (stop_routines(philo));
		(*philo) = (*philo)->next;
	}
	return (0);
}
