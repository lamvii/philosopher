/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-idri <ael-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 17:28:02 by ael-idri          #+#    #+#             */
/*   Updated: 2022/07/05 18:28:42 by ael-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	create_odd_threads(t_philo **philo)
{
	int	i;

	i = 0;
	while ((*philo) && ++i <= (*philo)->info->philo_nb)
	{
		if (pthread_create(&(*philo)->phi, NULL, philo_routin, (void *)*philo))
			return (FAILED);
		*philo = (*philo)->next->next;
		usleep(100);
	}
	return (SUCCESS);
}

int	create_pair_threads(t_philo **philo)
{
	int	i;

	i = 0;
	while ((*philo) && ++i <= ((*philo)->info->philo_nb / 2))
	{
		if (pthread_create(&(*philo)->phi, NULL, philo_routin, (void *)*philo))
			return (FAILED);
		*philo = (*philo)->next->next;
		usleep(100);
	}
	*philo = (*philo)->next;
	i = 1;
	while ((*philo) && ++i <= ((*philo)->info->philo_nb / 2) + 1)
	{
		if (pthread_create(&(*philo)->phi, NULL, philo_routin, (void *)*philo))
			return (FAILED);
		*philo = (*philo)->next->next;
		usleep(100);
	}
	return (SUCCESS);
}

int	create_threads(t_philo **philo)
{
	int	i;

	i = 0;
	if ((*philo)->info->philo_nb % 2)
		return (create_odd_threads(philo));
	else
		return (create_pair_threads(philo));
	return (SUCCESS);
}
