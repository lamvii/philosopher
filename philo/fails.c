/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fails.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-idri <ael-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 17:24:50 by ael-idri          #+#    #+#             */
/*   Updated: 2022/07/23 18:07:17 by ael-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	exit_philo(t_philo **philo, t_info **info)
{
	t_philo	*temp;

	if (*info)
	{
		if (pthread_mutex_destroy(&(*info)->message))
		{
			pthread_mutex_unlock(&(*info)->message);
			pthread_mutex_destroy(&(*info)->message);
		}
		free(*info);
	}
	while ((*philo))
	{
		if (pthread_mutex_destroy(&(*philo)->fork))
		{
			pthread_mutex_unlock(&(*philo)->fork);
			pthread_mutex_destroy(&(*philo)->fork);
		}
		temp = (*philo);
		*philo = (*philo)->next;
		free(temp);
	}
	return (1);
}

int	stop_create(t_philo **philo)
{
	t_philo	*temp;
	int		philo_nb;

	philo_nb = (*philo)->info->philo_nb;
	free((*philo)->info);
	while ((*philo) && philo_nb > 0)
	{
		if (pthread_mutex_destroy(&(*philo)->fork))
		{
			pthread_mutex_unlock(&(*philo)->fork);
			pthread_mutex_destroy(&(*philo)->fork);
		}
		temp = (*philo);
		*philo = (*philo)->next;
		free(temp);
		philo_nb--;
	}
	return (1);
}

int	stop_routines(t_philo **philo)
{
	t_philo	*temp;
	int		philo_nb;

	philo_nb = (*philo)->info->philo_nb;
	free((*philo)->info);
	while ((*philo) && philo_nb > 0)
	{
		if (pthread_mutex_destroy(&(*philo)->fork))
		{
			pthread_mutex_unlock(&(*philo)->fork);
			pthread_mutex_destroy(&(*philo)->fork);
		}
		temp = (*philo);
		*philo = (*philo)->next;
		free(temp);
		philo_nb--;
	}
	return (0);
}

int	fail_initialise(t_philo **philo, t_info **info)
{
	printf("fail initialise, programe will close ..\n");
	return (exit_philo(philo, info));
}

int	fail_create(t_philo **philo)
{
	printf("fail create philo threads, programe will close ..\n");
	return (stop_create(philo));
}
